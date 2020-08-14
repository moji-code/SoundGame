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
	// getter
	unsigned long get_occurrence_time() { return m_absolute_time; }
	unsigned long get_duration() { return m_duration; }
	unsigned char get_note_number() { return m_note_number; }
	// for debug
	void show();
};

#endif /* UtageNote_hpp */
