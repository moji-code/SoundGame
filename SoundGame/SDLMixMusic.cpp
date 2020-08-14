//
//  SDLMixMusic.cpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "SDLMixMusic.hpp"

SDLMixMusic::SDLMixMusic()
{
	m_pmusic = NULL;
}

SDLMixMusic::~SDLMixMusic()
{
	if (m_pmusic != NULL)
	{
		Mix_FreeMusic(m_pmusic);
		m_pmusic = 0;
	}
}

/*
 * initializes all about m_pmusic, then load a file
 */
bool SDLMixMusic::load_music(char *file_path)
{
	// initialize m_pmusic
	stop_music();					// halt if playing
	if (m_pmusic != NULL)
	{
		Mix_FreeMusic(m_pmusic);	// free if allocated
	}
	m_pmusic = 0;					// then, turn to 0

	// load a new music
	m_pmusic = Mix_LoadMUS(file_path);
	if (m_pmusic == 0)
	{
		return false;
	}
	
	return true;
}

/*
 * returns true when being played
 */
bool SDLMixMusic::is_playing()
{
	if (m_pmusic == 0)
	{
		return false;
	}
	
	if (Mix_PlayingMusic() == 0)
	{
		return false;
	}
	
	return true;
}

/*
 * plays a music if it has beeing loaded
 */
void SDLMixMusic::play_music(int num_of_loops)
{
	if (m_pmusic != 0)
	{
		Mix_PlayMusic(m_pmusic, num_of_loops);
	}
}

/*
 * fades out music in specified 'milli_second'
 */
void SDLMixMusic::fade_out_music(int milli_second)
{
	if (m_pmusic != 0)
	{
		Mix_FadeOutMusic(milli_second);
	}
}

/*
 * stop playing music immediately
 */
void SDLMixMusic::stop_music()
{
	if (m_pmusic != NULL)
	{
		Mix_HaltMusic();
	}
}
