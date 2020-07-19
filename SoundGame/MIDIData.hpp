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
	MIDIHeader m_header;
	vector<MIDITrack *> m_tracks;

public:
	~MIDIData();
	bool read(MIDIFile *pfile);
	// about track
	MIDITrack *get_track(string instrument_name);
	// for debug
	void show();
};

#endif /* MIDIData_hpp */
