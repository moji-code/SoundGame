//
//  MIDITrack.cpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <iostream>
using namespace std;

#include "MIDITrack.hpp"
#include "MIDIEvent.hpp"

/*
 * constructer
 */
MIDITrack::MIDITrack()
{
	m_track_length = 0;
}

/*
 * destructor
 */
MIDITrack::~MIDITrack()
{
	for (MIDIEvent *pevent : m_events)
	{
		delete pevent;
	}
	m_events.clear();
}

bool MIDITrack::read(MIDIFile *pfile)
{
	// if the track header was wrong
	if (pfile->check_header_ID("MTrk") == false)
	{
		// return false
		return false;
	}
	
	// read length of this track in the file
	m_track_length = pfile->read_sequential_data(4);	// header length

	// prepare running status byte
	unsigned char previous_status_byte = 0x00;

	// read events in this track
	while (pfile->eof() == false)
	{
		// create a new event and let it read data from file
		MIDIEvent *pnew_event = new MIDIEvent();
		pnew_event->read_a_event(pfile, previous_status_byte);

		// add the new event
		m_events.push_back(pnew_event);

		// now, if the new event was the end-of-track
		if (pnew_event->get_event_id() == MIDIEvent::end_of_track)
		{
			break;
		}
		
		// process running status
		if (pnew_event->is_midi_channel_message() == true)
		{
			previous_status_byte = pnew_event->get_status_byte();
		}
		else
		{
			previous_status_byte = 0x00;
		}
	}
	return true;
}

/*
 * about event
 */
string MIDITrack::get_instrument_name()
{
	// check each event
	for (MIDIEvent *pevent : m_events)
	{
		// if its id is instrument_name
		if (pevent->get_event_id() == MIDIEvent::event_id::instrument_name)
		{
			// return its name
			return pevent->get_instrument_name();
		}
	}
	
	// when no one matched, return ""
	return string("");
}


/*
 * show track information
 */
void MIDITrack::show()
{
	cout << endl;
	cout << "MTrk" << endl;
	cout << "----------" << endl;
	cout << "length: " << m_track_length << endl;
	
	for (MIDIEvent *pevent : m_events)
	{
		pevent->show();
	}
}

