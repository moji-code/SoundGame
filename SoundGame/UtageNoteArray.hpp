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
	
public:
	~UtageNoteArray();
	bool create(MIDIData *pmididata);
	// for debug
	void show();
};

#endif /* UtageNoteArray_hpp */
