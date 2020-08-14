//
//  MIDIEvent.cpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <iostream>
using namespace std;

#include "MIDIFile.hpp"
#include "MIDIEvent.hpp"

/*
 * constructer
 */
MIDIEvent::MIDIEvent()
{
	m_event_id = MIDIEvent::event_id::other;
	m_status_code = 0x00;
	m_delta_time = 0;
	m_is_note_number_already_set = false;
}

/*
 * read a event
 * <delta-time(:::)> <status_code(1)> <event-data(...)>
 */
void MIDIEvent::read_a_event(MIDIFile *pfile, unsigned char previous_status_code)
{
	// read delta time
	m_delta_time = pfile->read_variable_length_data();

	// read event code
	unsigned char first_byte = pfile->get_a_byte();
	unsigned char status_code;

	// set defalut value
	m_event_id = MIDIEvent::event_id::other;
	
	// the note number is NOT set yet
	m_is_note_number_already_set = false;

	/*-------------------------------------------------------*/
	// set event code
	/*-------------------------------------------------------*/
	// if the leftmost bit of first_byte is '0'
	if ((first_byte & 0x80) == 0x00)
	{
		// it is not an event code. it's a note number
		m_note_info.note_number = first_byte;
		m_is_note_number_already_set = true;

		// then use 'running status' = previous event's midi channel message
		status_code = previous_status_code;
	}
	// otherwise, the first_byte must be an status_code
	else
	{
		// then fill status_code with first_byte
		status_code = first_byte;
	}

	/*-------------------------------------------------------*/
	// if the code was a general event
	if (0x80 <= status_code && status_code <= 0xEF)
	{
		// save event code for next event's procedure of running status
		m_status_code = status_code;

		// and if it was 'note on'
		if ((status_code & 0xF0) == 0x90)
		{
			// then set the id 'note on'
			m_event_id = MIDIEvent::event_id::note_on;
			if (m_is_note_number_already_set == false)
			{
				m_note_info.note_number = pfile->get_a_byte();
			}
			m_note_info.velocity = pfile->get_a_byte();
//			skip_data(pfile, 1);	// for velocity
		}
		// if it was 'note off'
		else if ((status_code & 0xF0) == 0x80)
		{
			// then set the id 'note off'
			m_event_id = MIDIEvent::event_id::note_off;
			if (m_is_note_number_already_set == false)
			{
				m_note_info.note_number = pfile->get_a_byte();
			}
			m_note_info.velocity = pfile->get_a_byte();
//			skip_data(pfile, 1);	// for velocity
		}
		else
		{
			skip_general_midi_event_data(status_code, pfile);
		}
	}
	// if the code was a system exclusive
	else if (status_code == 0xF0 || status_code == 0xF7)
	{
		// skip following data
		skip_system_exclusive_data(pfile);
	}
	// if the code was a meta event
	else if (status_code == 0xFF)
	{
		// then read one more byte
		unsigned char meta_code = pfile->get_a_byte();
		// and if it was 'instrument name'
		if (meta_code == 0x04)
		{
			// read the name
			m_event_id = MIDIEvent::event_id::instrument_name;
			read_instrument_name(pfile);
		}
		// if it was 'tempo'
		else if (meta_code == 0x51)
		{
			// read the tempo information
			m_event_id = MIDIEvent::event_id::tempo;
			read_tempo(pfile);
		}
		// if it was 'end of track'
		else if (meta_code == 0x2F)
		{
			// set event id
			m_event_id = MIDIEvent::event_id::end_of_track;
			// skip a byte that represent num of bytes following this
			// (that is 0x00)
			pfile->get_a_byte();
		}
		// otherwise,
		else
		{
			// skip meta data that follows it
			skip_meta_event(meta_code, pfile);
		}
	}
}

// read event data
//
// read instrument name
void MIDIEvent::read_instrument_name(MIDIFile *pfile)
{
	// get name's length
	unsigned long length = pfile->read_variable_length_data();
	char letter;
	// init string
	m_instrument_name.clear();

	// construct instrument name byte by byte
	for (unsigned long i = 0; i < length; i++)
	{
		letter = pfile->get_a_byte();
		m_instrument_name.push_back(letter);
	}
}

// read tempo information
void MIDIEvent::read_tempo(MIDIFile *pfile)
{
	// skip a byte (it may be 0x03)
	pfile->get_a_byte();
	// read tempo information that consist of 3 bytes
	m_tempo = pfile->read_fixed_length_data(3);
}

/*
 * skip other data
 */
void MIDIEvent::skip_data(MIDIFile *pfile, unsigned long size)
{
	// skip 'size' bytes
	for (unsigned long i = 0; i < size; i++)
	{
		pfile->get_a_byte();
	}
}

// skip general midi events
// 0x80~0xE0     have 2 bytes after them
// 0xC0 and 0xD0 have 1 byte  after them
void MIDIEvent::skip_general_midi_event_data(unsigned char status_code, MIDIFile *pfile)
{
	switch (status_code & 0xF0)
	{
		case 0x80:	// note off
		case 0x90:	// note on
		case 0xA0:	// polyphonic pressure
		case 0xB0:	// control change
		case 0xE0:	// pitch bend
			skip_data(pfile, 2);
			break;

		case 0xC0:	// program change
		case 0xD0:	// channel pressure
			skip_data(pfile, 1);
			break;
	}
}

// skip system exclusive data
void MIDIEvent::skip_system_exclusive_data(MIDIFile *pfile)
{
	// first, read the length of SysEx
	unsigned long length = pfile->read_variable_length_data();
	
	// skip all detail data
	skip_data(pfile, length);
}

void MIDIEvent::skip_meta_event(unsigned char meta_code, MIDIFile *pfile)
{
	// first, read the length of meta event data
	unsigned long length = pfile->read_variable_length_data();
	
	// skip all detail data
	skip_data(pfile, length);
}

/*
 * for debug
 */
void MIDIEvent::show()
{
	switch (m_event_id)
	{
		case event_id::note_off:
			cout << "note off " << dec << int(m_note_info.note_number) << " (0x"  << hex << int(m_note_info.note_number) << ")" << endl;
			break;

		case event_id::note_on:
			cout << "note on " << dec << int(m_note_info.note_number)
			<< hex << " (0x" << int(m_note_info.note_number) << ") v:" << dec << int(m_note_info.velocity) << " (0x" << hex << int(m_note_info.velocity) << ")" << endl;
			break;
			
		case event_id::instrument_name:
			cout << "instrument name: " << m_instrument_name << endl;
			break;
			
		case event_id::tempo:
			cout << "tempo: " << m_tempo << endl;
			break;
			
		case event_id::end_of_track:
			cout << "end of track" << endl;
			break;
			
		default:
			cout << "other" << endl;
			break;
	}
}

// returns true when this event has a 'midi channel message'
bool MIDIEvent::is_midi_channel_message()
{
	return (0x80 <= m_status_code && m_status_code <=0xef) ? true : false;
}
