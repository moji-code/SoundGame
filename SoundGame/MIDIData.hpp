//
//  MIDIData.hpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef MIDIData_hpp
#define MIDIData_hpp

#include <vector>
using namespace std;

#include "sdl.h"
#include "MIDIHeader.hpp"
#include "MIDIFile.hpp"
#include "MIDITrack.hpp"
#include "MIDIEvent.hpp"

class MIDIData
{
protected:
	MIDIHeader m_header;				// MIDI Header
	vector<MIDITrack *> m_tracks;		// MIDI Tracks
	// about time
	bool m_is_tempo_gotten = false;
	unsigned long m_gotten_tempo;

public:
	~MIDIData();
	bool read(string file_name);
	// about track
	MIDITrack *get_track(string instrument_name);
	// about time
	unsigned long get_tempo();
	unsigned long get_real_time(unsigned long delta_time);
	double get_quarter_note_time_ratio();
	// for debug
	void show();
};

#endif /* MIDIData_hpp */
