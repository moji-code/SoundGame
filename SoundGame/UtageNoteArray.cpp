//
//  UtageNoteArray.cpp
//  SoundGame
//
//  Created by mojito on 2020/07/15.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <iostream>
using namespace std;

#include "UtageNoteArray.hpp"
#include "UtageNote.hpp"

/*
 * destrcuter that delete all notes
 */
UtageNoteArray::~UtageNoteArray()
{
	for (UtageNote *pnote : m_utage_notes)
	{
		delete pnote;
	}
	m_utage_notes.clear();
}

/*
 * create utage notes from MIDIData
 */
// helper: calc duration time between it and its corresponding 'note_on'
unsigned long UtageNoteArray::get_duration_from(vector<MIDIEvent *>::iterator it, vector<MIDIEvent *>::iterator end)
{
	// get a note number of the current event
	unsigned char note_number = (*it)->get_note_number();
	// reset duretion time that will be returned
	unsigned long duration_time = 0;

	// until it reaches the end of the array of events
	while (it != end)
	{
		// at first, move it to the next event
		it++;
		// add the 'delta time' of the event to the 'duration time'
		duration_time += (*it)->get_delta_time();

		// if the event is 'note off' and the note's pitch is same as specified 'note on''s
		if ((*it)->get_event_id() == MIDIEvent::event_id::note_off &&
			(*it)->get_note_number() == note_number)
		{
			// we got the corresponding 'note off', then return the calculated duration time
			return duration_time;
		}
	}

	// fatal error: no corresponding note_off event
	assert(false);
}

// create utage note array
bool UtageNoteArray::create(MIDIData *pmididata)
{
	// get track data for notes that is used in Utage
	MIDITrack *ptrack = pmididata->get_track(UTAGE_INSTRUMENT_SIGNATURE);

	// if no track was found
	if (ptrack == NULL)
	{
		// return immediately
		return false;
	}

	// get begin and end of events
	auto begin_of_events = ptrack->get_begin_of_events();
	auto end_of_events   = ptrack->get_end_of_events();
	
	// reset current time
	unsigned long current_time = 0;
	unsigned long duration = 0;
	
	// continue until it points at the end of event
	auto it = begin_of_events;
	while (it != end_of_events)
	{
		// increase current_time by the delta time
		current_time += (*it)->get_delta_time();
		// if the event is 'note on'
		if ((*it)->get_event_id() == MIDIEvent::event_id::note_on)
		{
			// then calc duration time of this note by finding note off that corresponds this note on
			duration = get_duration_from(it, end_of_events);
			
			// create a new note
			UtageNote *pnew_note = new UtageNote();
			// and initialize it with *it that represents a midi event and the duration time
			pnew_note->init(*it, current_time, duration);
			// store it at the end
			m_utage_notes.push_back(pnew_note);
		}
		
		it++;
	}
	
	return true;
}

/*
 * for debug
 */
void UtageNoteArray::show()
{
	cout << endl << "UtageNoteArray:" << endl << "------" << endl;
	for (UtageNote *pnote : m_utage_notes)
	{
		pnote->show();
	}
}

