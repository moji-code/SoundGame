//
//  MIDITrack.hpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef MIDITrack_hpp
#define MIDITrack_hpp

#include <vector>

#include "sdl.h"
#include "MIDIFile.hpp"
#include "MIDIEvent.hpp"

class MIDITrack
{
protected:
	unsigned long m_track_length;
	vector<MIDIEvent *> m_events;		// MIDI Events

public:
	MIDITrack();
	~MIDITrack();
	bool read(MIDIFile *pfile);
	// about event
	string get_instrument_name();
	unsigned long get_tempo();
	vector<MIDIEvent *>::iterator get_begin_of_events() { 	return m_events.begin(); }
	vector<MIDIEvent *>::iterator get_end_of_events() { return m_events.end(); }
	// for debug
	void show(int track_num);
};

#endif /* MIDITrack_hpp */
