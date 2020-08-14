//
//  SDLMixChunk.cpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "SDLMixChunk.hpp"

SDLMixChunk::SDLMixChunk()
{
	m_pchunk = NULL;
	m_channel_number = -1;
}

SDLMixChunk::~SDLMixChunk()
{
	if (m_pchunk != NULL)
	{
		Mix_FreeChunk(m_pchunk);
		m_pchunk = NULL;
	}
}

/*
 * load a wave of sound
 */
bool SDLMixChunk::load_wave(int sound_id, char *file_path)
{
	m_pchunk = Mix_LoadWAV(file_path);
	if (m_pchunk == NULL)
	{
		return false;
	}

	m_id = sound_id;
	return true;
}

/*
 * play the sound
 */
void SDLMixChunk::play(int num_of_loops, int channel_number)
{
	if (m_pchunk == NULL)
	{
		return;
	}
	/*
	if (Mix_Playing(m_channel_number) != 0)
	{
		return;
	}
	 */
	
	m_channel_number = Mix_PlayChannel(channel_number, m_pchunk, num_of_loops);
	printf("sound chunk: %d\n", channel_number);
}

/*
 * returns true, when playing the sound
 */
bool SDLMixChunk::is_playing()
{
	if (m_pchunk != NULL && m_channel_number != -1)
	{
		if (Mix_Playing(m_channel_number) == 1)
		{
			return true;
		}
	}
	
	return false;
}

/*
 * stop sound
 */
void SDLMixChunk::stop_sound()
{
	Mix_HaltChannel(m_channel_number);
}

