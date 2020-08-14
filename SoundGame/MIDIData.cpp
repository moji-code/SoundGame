//
//  MIDIData.cpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "MIDIData.hpp"

/*
 * destructer
 *  that delete tracks if exits
 */
MIDIData::~MIDIData()
{
	for (MIDITrack *ptrack : m_tracks)
	{
		delete ptrack;
	}

	m_tracks.clear();
}

/*
 * read MIDI header & MIDI tracks
 */
bool MIDIData::read(string file_name)
{
	// if failed to open file
	MIDIFile midi_file;
	if (midi_file.open(file_name) == false)
	{
		// return
		return false;
	}

	// if failed to read header of midi file
	if (m_header.read(&midi_file) == false)
	{
		// return
		return false;
	}
	
	// read tracks
	while (midi_file.eof() == false)
	{
		MIDITrack *pnew_track = new MIDITrack();
		if (pnew_track->read(&midi_file) == false)
		{
			delete pnew_track;
			return false;
		}
		m_tracks.push_back(pnew_track);
	}

	return true;
}

/*
 * about track
 */
MIDITrack * MIDIData::get_track(string instrument_name)
{
	// check each track
	for (MIDITrack *ptrack : m_tracks)
	{
		// if its instrument name is same as the one specified
		if (ptrack->get_instrument_name() == instrument_name)
		{
			// then return it
			return ptrack;
		}
	}
	
	// when no one matched, return NULL
	return NULL;
}

/*
 * about time
 */

// calc real time in milli second
unsigned long MIDIData::get_real_time(unsigned long delta_time)
{
	unsigned long tempo = get_tempo();
	unsigned long time_base = m_header.get_time_base();

//	return ((60./double(tempo)) * double(delta_time)/double(time_base))*1000;
	return ((double(tempo)/1000000) *double(delta_time)/double(time_base))*1000;
}

// returns quarter note time in milliseconds
//  searching events in tracks
double MIDIData::get_quarter_note_time_ratio()
{
	unsigned long tempo = get_tempo();
	unsigned long time_base = m_header.get_time_base();
	
	double quarter_note_time_in_millisecond;
	
	quarter_note_time_in_millisecond = 60*1000/tempo;
	
	return quarter_note_time_in_millisecond / time_base;
	
	/*
		delta_time = 960
	 
		tempo = 120
		time_base = 480
	 
		quarter_note_time = 60/tempo
		
		delta_time * ( quarter_note_time /time_base )
		               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 */
}

// get tepo searching events in tracks
unsigned long MIDIData::get_tempo()
{
	if (m_is_tempo_gotten == true)
	{
		return m_gotten_tempo;
	}
	
	m_gotten_tempo = 0;

	// call 'get tempo' about each track
	for (MIDITrack *ptrack : m_tracks)
	{
		m_gotten_tempo = ptrack->get_tempo();
		// if tempo is not 0
		if (m_gotten_tempo != 0)
		{
			// then its the true tempo
			return m_gotten_tempo;
		}
	}
	
	// otherwise returns 0 for error
	return m_gotten_tempo;
}


/*
 * show information
 */
void MIDIData::show()
{
	// show header information
	m_header.show();

	// show each track information
	int track_num = 1;
	for (MIDITrack *ptrack : m_tracks)
	{
		ptrack->show(track_num);
		track_num++;
	}
}
