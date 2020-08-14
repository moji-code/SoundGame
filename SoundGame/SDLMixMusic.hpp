//
//  SDLMixMusic.hpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLMixMusic_hpp
#define SDLMixMusic_hpp

#include "sdl.h"

class SDLMixMusic
{
protected:
	Mix_Music *m_pmusic;

public:
	SDLMixMusic();
	~SDLMixMusic();
	bool load_music(char *file_path);
	bool is_playing();
	void play_music(int num_of_loops);
	void fade_out_music(int milli_second);
	void stop_music();
};

#endif /* SDLMixMusic_hpp */
