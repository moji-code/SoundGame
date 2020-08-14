//
//  UtageNotesShow.cpp
//  SoundGame
//
//  Created by mojito on 2020/08/07.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <vector>

#include "SDLTimer.hpp"

#include "UtageNotesShow.hpp"
#include "utage.h"

// constructer
UtageNotesShow::UtageNotesShow()
{
	m_pnotes = 0;
	init_sdl();
}

// init sdl, mixer
void UtageNotesShow::init_sdl()
{
	// following will also initialize IMG and MIX
	m_sdl.init(GAME_MAGNIFICATION);
	
	// create window
	m_sdl.create_window("Utage", GAME_WIDTH_BY_DOT, GAME_HEIGHT_BY_DOT);
}


// load audio file onto SDLMixer
void UtageNotesShow::load_audio(string audio_file_name)
{
	m_sdl.load_music((char *)audio_file_name.c_str());
}

// set notes and save information in UtageNoteArray
void UtageNotesShow::set_notes(UtageNoteArray *pnotes)
{
	m_pnotes = pnotes;

	// calc seconds in a lane
	unsigned long tempo = pnotes->get_tempo();
	m_second_in_lane = (double(tempo)/1000000)*1000*4*TIMING_MEASURES_IN_LANE;
}

// run
void UtageNotesShow::run()
{
	// start timer
	SDLTimer frame_timer;
	SDLTimer music_timer;

	// start music
	m_sdl.play_music(1);

	// a simple game loop
	while (is_quit_button_pushed() == false)
	{
		// draw background
		draw_background();
		
		// draw notes
		draw_notes(music_timer);
		
		// flip flop
		m_sdl.update_window();

		// wait by frame ratio
		check_and_wait_frame_ratio(frame_timer);
	}
}


// returns true when process should be end
// otherwise false, check if CMD+'Q' or the RED Button is pushed
bool UtageNotesShow::is_quit_button_pushed()
{
	SDL_Event e;
	// if there are events that has not been handled
	while (SDL_PollEvent(&e) == 1)
	{
		// handle the one of them -
		//  if CMD+'Q' or RED button is pushed
		if (e.type == SDL_QUIT)
		{
			// return sending sign to quit process
			return true;
		}
	}
	return false;
}

// draws background
void UtageNotesShow::draw_background()
{
	// fill background
	SDL_Rect rect = { 0, 0, GAME_WIDTH_BY_DOT, GAME_HEIGHT_BY_DOT };
	m_sdl.fill_rect(rect, m_sdl.get_color_code_from_rgb(63, 43, 86));

	// draw lane's lines
	SDL_Point p1, p2;
	p1.y = GAME_LANE_TOP_BY_DOT;
	p2.y = GAME_LANE_BOTTOM_BY_DOT;
	for (int i = 0; i < GAME_NUM_OF_LANES + 1; i ++)
	{
		p1.x = GAME_LANE_LEFT_BY_DOT + GAME_LANE_WIDTH_BY_DOT * i;
		p2.x = p1.x;
		for (int j = 0; j < 6; j++)
		{
			m_sdl.draw_line(p1, p2, m_sdl.get_color_code_from_rgb(252 - j*25, 219 - j*25, 37 + j*12));
			p1.x += 1;
			p2.x += 1;
		}
	}
}

// draws notes
void UtageNotesShow::draw_notes(SDLTimer &music_timer)
{
	// calc time range to show
	unsigned long begin, end;
	
	begin = music_timer.get_ticks();
	end   = begin + m_second_in_lane;

	// build up notes
	vector<UtageNote *> note_array = m_pnotes->get_notes_between(begin, end);
	
	// prepare parameters
	SDL_Point p1, p2;
	p1.x = 0;
	p2.x = GAME_WIDTH_BY_DOT;
	Uint32 color_code = m_sdl.get_color_code_from_rgb(255, 128, 128);
	
	// draw
	unsigned long occurrence_time;
	int y_pos;
	for (UtageNote *pnote : note_array)
	{
		occurrence_time = pnote->get_occurrence_time() - begin;

		y_pos = GAME_LANE_BOTTOM_BY_DOT - GAME_HEIGHT_BY_DOT*double(occurrence_time)/m_second_in_lane;
		
		p1.x = GAME_LANE_LEFT_BY_DOT + (pnote->get_note_number() - MIDI_FIRST_NOTE_NUMBER)*GAME_NOTE_WIDTH_BY_DOT;
		p2.x = p1.x + GAME_NOTE_WIDTH_BY_DOT;

		for (int i = -3; i <= 3; i++)
		{
			p1.y = p2.y = y_pos + i;
			m_sdl.draw_line(p1, p2, color_code);
		}
	}
}

// game wait
void UtageNotesShow::check_and_wait_frame_ratio(SDLTimer &frame_timer)
{
	Uint32 time_pass = frame_timer.get_ticks();
	if (time_pass < TIMING_FRAME_TIME)
	{
		SDL_Delay(TIMING_FRAME_TIME - time_pass);
	}
}
