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
bool MIDIData::read(MIDIFile *pfile)
{

	// if failed to read header of midi file
	if (m_header.read(pfile) == false)
	{
		// return
		return false;
	}
	
	// read tracks
	while (pfile->eof() == false)
	{
		MIDITrack *pnew_track = new MIDITrack();
		if (pnew_track->read(pfile) == false)
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
 * show information
 */
void MIDIData::show()
{
	// show header information
	m_header.show();

	// show each track information
	for (MIDITrack *ptrack : m_tracks)
	{
		ptrack->show();
	}
}
