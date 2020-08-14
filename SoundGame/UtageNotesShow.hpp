//
//  UtageNotesShow.hpp
//  SoundGame
//
//  Created by mojito on 2020/08/07.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef UtageNotesShow_hpp
#define UtageNotesShow_hpp

#include <string>

#include "sdl.h"

#include "SDLEnvironment.hpp"
#include "SDLMixer.hpp"
#include "SDLTimer.hpp"

#include "utage.h"
#include "UtageNoteArray.hpp"

class UtageNotesShow
{
protected:
	SDLEnvironment 	m_sdl;
	UtageNoteArray *m_pnotes;
	unsigned long m_second_in_lane;
	
	void init_sdl();
	bool is_quit_button_pushed();
	void draw_background();
	void draw_notes(SDLTimer &music_timer);
	void check_and_wait_frame_ratio(SDLTimer &frame_timer);
	
	void move_notes();
	
	bool is_time_to_move_notes(int *pframe_count);
	
public:
	UtageNotesShow();
	void set_notes(UtageNoteArray *pnotes);
	void load_audio(string audio_file_name);
	void run();
};

#endif /* UtageNotesShow_hpp */
