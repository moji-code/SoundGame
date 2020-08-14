//
//  SDLMixSound.cpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "SDLMixSound.hpp"

SDLMixSound::SDLMixSound()
{
	
}

SDLMixSound::~SDLMixSound()
{
	size_t num_of_chunks = m_chunks.size();
	for (size_t cur_chunk_index = 0; cur_chunk_index < num_of_chunks; cur_chunk_index++)
	{
		delete m_chunks.at(cur_chunk_index);
	}
	m_chunks.clear();
}

/*
 * create a new chunk to load the sound, and push_back the chunk to the vector
 */
bool SDLMixSound::load_sound(int sound_id, char *file_path)
{
	SDLMixChunk *pnew_chunk = new SDLMixChunk();
	if (pnew_chunk->load_wave(sound_id, file_path) == false)
	{
		delete pnew_chunk;
		return false;
	}
	
	m_chunks.push_back(pnew_chunk);
	return true;
}

/*
 * find the chunk that has the specified sound_id, and play it when found it
 */
bool SDLMixSound::play_sound(int sound_id, int num_of_loops, int channel_number)
{
	SDLMixChunk *pchunk = find_chunk_of(sound_id);
	if (pchunk == NULL)
	{
		return false;
	}
	
	pchunk->play(num_of_loops, channel_number);
	return true;
}

/*
 * returns true, if even one chunk is playing something
 */
bool SDLMixSound::is_playing()
{
	for (SDLMixChunk *pchunk : m_chunks)
	{
		if (pchunk->is_playing() == true)
		{
			return true;
		}
	}
	
	return false;
}


/*
 * returns the pointer to the chunk that has the specified sound_id, when found it
 *  or NULL otherwise
 */
SDLMixChunk *SDLMixSound::find_chunk_of(int sound_id)
{
	for (SDLMixChunk *pchunk : m_chunks)
	{
		if (pchunk->get_sound_id() == sound_id)
		{
			return pchunk;
		}
	}

	return NULL;
}

#if 0
/*
 * stop all sound
 */
void SDLMixSound::stop_all_sounds()
{
	for (SDLMixChunk *pchunk : m_chunks)
	{
		pchunk->stop_all_sound();
	}
}
#endif

/*
 * stop specified sound
 */
void SDLMixSound::stop_sound(int sound_id)
{
	for (SDLMixChunk *pchunk : m_chunks)
	{
		if (pchunk->get_sound_id() == sound_id)
		{
			pchunk->stop_sound();
			return;
		}
	}
}
