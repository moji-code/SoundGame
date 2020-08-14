//
//  SDLMixChunk.hpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLMixChunk_hpp
#define SDLMixChunk_hpp

#include "sdl.h"

class SDLMixChunk
{
protected:
	int m_id;
	Mix_Chunk *m_pchunk;
	int m_channel_number;

public:
	SDLMixChunk();
	virtual ~SDLMixChunk();
	bool load_wave(int sound_id, char *file_path);
	void play(int num_of_loops, int channel_number);
	bool is_playing();
	int get_sound_id() { return m_id; }
	void stop_sound();
};

#endif /* SDLMixChunk_hpp */
