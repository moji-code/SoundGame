//
//  MIDIEvent.hpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef MIDIEvent_hpp
#define MIDIEvent_hpp

#include <string>
using namespace std;

#include "sdl.h"
#include "MIDIFile.hpp"

class MIDIEvent
{
protected:
	// general parameters
	int m_event_id;
	unsigned long m_delta_time;
	// internal parameters
	unsigned char m_previous_status_code;
	unsigned char m_status_code;
	
	// particular parameters
	string m_instrument_name;
	union
	{
		unsigned long m_tempo;			// occupies 3 bytes
		struct
		{
			unsigned char note_number;	// occupies 1 byte
			unsigned char velocity;		// occupies 1 byte
		} m_note_info;
	};
	bool m_is_note_number_already_set;
	
	// read event data
	void read_instrument_name(MIDIFile *pfile);
	void read_tempo(MIDIFile *pfile);
	
	
	// skip other data
	void skip_data(MIDIFile *pfile, unsigned long size);
	void skip_general_midi_event_data(unsigned char event_code, MIDIFile *pfile);
	void skip_system_exclusive_data(MIDIFile *pfile);
	void skip_meta_event(unsigned char meta_code, MIDIFile *pfile);
	

public:
	MIDIEvent();
	void read_a_event(MIDIFile *pfile, unsigned char previous_status_code);

	// about attributes
	unsigned long get_delta_time() { return m_delta_time; }
	int get_event_id() { return m_event_id; }
	unsigned char get_note_number() { return m_note_info.note_number; }
	unsigned char get_velocity() { return m_note_info.velocity; }
	enum event_id
	{
		end_of_track, note_off, note_on, tempo, instrument_name,
		other
	};
	string get_instrument_name() { return m_instrument_name; }
	unsigned long get_tempo() { return m_tempo; }
	bool is_midi_channel_message();
	unsigned char get_status_byte() { return m_status_code; }
	// for debug
	void show();
};

#endif /* MIDIEvent_hpp */
