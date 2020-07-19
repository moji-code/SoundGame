//
//  MIDIHeader.hpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef MIDIHeader_hpp
#define MIDIHeader_hpp

#include "sdl.h"
#include "MIDIFile.hpp"

class MIDIHeader
{
protected:
	unsigned long m_header_length;
	unsigned long m_format;
	unsigned long m_num_of_tracks;
	unsigned long m_time_base;

public:
	MIDIHeader();
	bool read(MIDIFile *pfile);
	// for debug
	void show();
};

#endif /* MIDIHeader_hpp */
