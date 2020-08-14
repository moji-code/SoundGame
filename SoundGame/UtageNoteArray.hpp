//
//  UtageNoteArray.hpp
//  SoundGame
//
//  Created by mojito on 2020/07/15.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef UtageNoteArray_hpp
#define UtageNoteArray_hpp

#include <vector>
using namespace std;

#include "sdl.h"
#include "UtageNote.hpp"
#include "MIDIData.hpp"

#define UTAGE_INSTRUMENT_SIGNATURE	"Utage Notes"

class UtageNoteArray
{
protected:
	vector<UtageNote *> m_utage_notes;
	unsigned long get_duration_from(vector<MIDIEvent *>::iterator it, vector<MIDIEvent *>::iterator end);
	bool is_end_of_note_on(vector<MIDIEvent *>::iterator it, unsigned char note_number);
	unsigned long m_tempo = 0;
	
	// for search optimization
	vector<UtageNote *>::iterator m_itr_last_searched_note;
	unsigned long m_last_begin_for_search = ULONG_MAX;
	
public:
	~UtageNoteArray();
	bool create(MIDIData *pmididata);
	vector<UtageNote *> get_notes_between(unsigned long begin, unsigned long end);
	unsigned long get_tempo() { return m_tempo; }
	// for debug
	void show();
};

#endif /* UtageNoteArray_hpp */
