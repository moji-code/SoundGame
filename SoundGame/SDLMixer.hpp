//
//  SDLMixer.hpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLMixer_hpp
#define SDLMixer_hpp

#include "sdl.h"
#include "SDLMixSound.hpp"
#include "SDLMixMusic.hpp"

class SDLMixer
{
protected:
	SDLMixSound m_sound;
	SDLMixMusic m_music;
	int m_num_of_max_channel;
	int m_cur_channel_number;
	
public:
	// initialization
	SDLMixer();
	~SDLMixer();
	bool init(int flags_of_libralies);

	// about sound
	bool load_sound(int sound_id, char *file_path);
	void play_sound(int sound_id, int num_of_loops);
	bool is_playing_sound();
	void stop_all_sounds() { Mix_HaltChannel(-1); }
	void stop_sound(int sound_id) { m_sound.stop_sound(sound_id); };

	// about music
	bool load_music(char *file_path);
	void play_music(int num_of_loops);
	bool is_playing_music();
	void stop_music() { m_music.stop_music(); }
	
	// about both of sound and music
	bool is_playing_anything();
};

#endif /* SDLMixer_hpp */
