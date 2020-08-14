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
		if (is_end_of_note_on(it, note_number) == true)
		{
			// we got the corresponding 'note off', then return the calculated duration time
			return duration_time;
		}
	}

	// fatal error: no corresponding note_off event
 	assert(false);
}

// check the end of 'note_on' that searches
//	(1) note_off
//	(2) note_on with 0 velocity
bool UtageNoteArray::is_end_of_note_on(vector<MIDIEvent *>::iterator it, unsigned char note_number)
{
	// (1) note_off
	if ((*it)->get_event_id() == MIDIEvent::event_id::note_off &&
		(*it)->get_note_number() == note_number)
	{
		return true;
	}
	
	// (2) note_on with 0 velocity
	if ((*it)->get_event_id() == MIDIEvent::event_id::note_on &&
		(*it)->get_note_number() == note_number &&
		(*it)->get_velocity() == 0)
	{
		return true;
	}
	
	return false;
}

// create utage note array
bool UtageNoteArray::create(MIDIData *pmididata)
{
	// save information of MIDIData
	m_tempo = pmididata->get_tempo();
	
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
		current_time += pmididata->get_real_time((*it)->get_delta_time());
		// if the event is 'note on'
		if ((*it)->get_event_id() == MIDIEvent::event_id::note_on &&
			(*it)->get_velocity() != 0)
		{
			// debug
			if ((*it)->get_event_id() == MIDIEvent::event_id::note_on)
			{
				cout << hex << (*it)->get_note_number() << ", velocity=" << hex << "0x" << int((*it)->get_velocity()) << " (" <<
				dec << int((*it)->get_velocity()) << ")" << endl;
			}

			// then calc duration time of this note by finding note off that corresponds this note on
			duration = pmididata->get_real_time(get_duration_from(it, end_of_events));
			
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

// create and return notes array that is between start and end
vector<UtageNote *> UtageNoteArray::get_notes_between(unsigned long begin, unsigned long end)
{
	vector<UtageNote *> note_array;

	/*
	 * initialize itr
	 */
	// if it's the first time to search notes or rewinding time
	if (begin < m_last_begin_for_search)
	{
		// set iterator to the begin of notes
		m_itr_last_searched_note = m_utage_notes.begin();
	}

	
	/*
	 * skip until the specified time is found
	 */
	while ((*m_itr_last_searched_note)->get_occurrence_time() < begin)
	{
		// increment iterator
		m_itr_last_searched_note++;

		// if it reached the end of notes
		if (m_itr_last_searched_note == m_utage_notes.end())
		{
			// return
			return note_array;	// maybe empty
		}
	}

	
	/*
	 * build up array
	 */
	while ((*m_itr_last_searched_note)->get_occurrence_time() < end)
	{
		// add a note to the array
		note_array.push_back(*m_itr_last_searched_note);
		
		// increment iterator
		m_itr_last_searched_note++;

		// if it reached the end of notes
		if (m_itr_last_searched_note == m_utage_notes.end())
		{
			// break out of this loop
			break;
		}
	}

	return note_array;
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

