//
//  SDLTimer.hpp
//  SoundGame
//
//  Created by mojito on 2020/08/08.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLTimer_hpp
#define SDLTimer_hpp

#include "sdl.h"

class SDLTimer
{
protected:
	Uint32 m_ticks;
public:
	SDLTimer() { start(); }
	void start() { m_ticks = SDL_GetTicks(); }
	Uint32 get_ticks() { return SDL_GetTicks() - m_ticks; }
};

#endif /* SDLTimer_hpp */
