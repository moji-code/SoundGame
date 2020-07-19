//
//  UtageNote.cpp
//  SoundGame
//
//  Created by mojito on 2020/07/15.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <iostream>
using namespace std;

#include "UtageNote.hpp"

/*
 * initialize reffering a MIDIEvent instance
 */
void UtageNote::init(MIDIEvent *pevent, unsigned long absolute_time, unsigned long duration)
{
	m_absolute_time = absolute_time;
	m_duration = duration;
	m_note_number = pevent->get_note_number();
}

/*
 * for debug
 */

void UtageNote::show()
{
	cout << "note: " << int(m_note_number) << " from: " << m_absolute_time << " size: " << m_duration << endl;
}
