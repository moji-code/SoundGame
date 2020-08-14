//
//  SDLMixSound.hpp
//  SDLMixer
//
//  Created by maruyama on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLMixSound_hpp
#define SDLMixSound_hpp

#include <vector>
#include "sdl.h"
#include "SDLMixChunk.hpp"

using namespace std;

class SDLMixSound
{
protected:
	vector<SDLMixChunk*> m_chunks;
	SDLMixChunk *find_chunk_of(int sound_id);
	
public:
	SDLMixSound();
	virtual ~SDLMixSound();
	bool load_sound(int sound_id, char *file_path);
	bool play_sound(int sound_id, int num_of_loops, int channel_number);
	bool is_playing();
//	void stop_all_sounds();
	void stop_sound(int sound_id);
};

#endif /* SDLMixSound_hpp */
