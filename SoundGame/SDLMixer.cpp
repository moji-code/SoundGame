//
//  SDLMixer.cpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "SDLMixer.hpp"

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// initialization
SDLMixer::SDLMixer()
{
	m_num_of_max_channel = 16;
	m_cur_channel_number = 0;
}

SDLMixer::~SDLMixer()
{
	Mix_CloseAudio();
	Mix_Quit();
}
bool SDLMixer::init(int flags_of_libralies)
{
	//
	if (Mix_Init(flags_of_libralies) != flags_of_libralies)
	{
		return false;
	}
	
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) ==-1)
	{
		return false;
	}
	
	// allocate max channel num to m_num_of_max_channel
	Mix_AllocateChannels(m_num_of_max_channel);
	
	return true;
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// about sound
bool SDLMixer::load_sound(int sound_id, char *file_path)
{
	return m_sound.load_sound(sound_id, file_path);
}

void SDLMixer::play_sound(int sound_id, int num_of_loops)
{
	m_sound.play_sound(sound_id, num_of_loops, m_cur_channel_number);
	m_cur_channel_number = (m_cur_channel_number + 1) % m_num_of_max_channel;
}

bool SDLMixer::is_playing_sound()
{
	return m_sound.is_playing();
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// about music
bool SDLMixer::load_music(char *file_path)
{
	return m_music.load_music(file_path);
}

void SDLMixer::play_music(int num_of_loops)
{
	m_music.play_music(num_of_loops);
}

bool SDLMixer::is_playing_music()
{
	return m_music.is_playing();
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// about both of sound and music
bool SDLMixer::is_playing_anything()
{
	return (is_playing_sound() == true || is_playing_music() == true) ? true : false;
}

