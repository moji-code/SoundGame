//
//  UtageNote.hpp
//  SoundGame
//
//  Created by mojito on 2020/07/15.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef UtageNote_hpp
#define UtageNote_hpp

#include "sdl.h"
#include "MIDIEvent.hpp"

class UtageNote
{
protected:
	unsigned long m_absolute_time;
	unsigned long m_duration;
	unsigned char m_note_number;

public:
	void init(MIDIEvent *pevent, unsigned long absolute_time, unsigned long duration);
	// for debug
	void show();
};

#endif /* UtageNote_hpp */
