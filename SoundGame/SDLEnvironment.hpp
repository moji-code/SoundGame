//
//  SDLEnvironment.hpp
//
//  Created by mojito on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

/*
 * updated on 2020/08/07
 *	ADD: draw line
 */

#ifndef SDLEnvironment_hpp
#define SDLEnvironment_hpp

#include "sdl.h"
#include "SDLMixer.hpp"

class SDLEnvironment
{
protected:
	int m_window_width, m_window_height;
	float m_magnification;
	SDL_Window *m_pwindow;
	SDL_Renderer *m_prenderer;

	// initiaation flags
	bool m_sdl_initialized;
	bool m_img_initialized;
	bool m_mix_initialized;

//	SDL_Surface *get_window_surface();
	SDL_Renderer *get_window_renderer() { return m_prenderer; }
	
	// about line slope
	int get_slope(SDL_Point p1, SDL_Point p2);
	enum
	{
		horizontal, vertical
	};
	
	// about SDL mixer
	SDLMixer m_mixer;

public:
	SDLEnvironment();
	virtual ~SDLEnvironment();
	/*
	 * about window
	 */
	bool init(float magnification);
	bool create_window(const char* title, int x, int y, int w, int h, Uint32 flags);
	bool create_window(const char* title, int w, int h);
	int get_window_width()  { return m_window_width; }
	int get_window_height() { return m_window_height; }
	/*
	 * draw & show
	 */
	void blit_image(SDL_Surface *image, SDL_Rect *src, int dest_x, int dest_y, double ratio);
	void blit_image(SDL_Texture *ptexture, SDL_Rect *src, int dest_x, int dest_y, double ratio);
	void update_window();
	void fill_rect(SDL_Rect rect, Uint32 color_code);
	Uint32 get_color_code_from_rgb(int red, int green, int blue, int alpha = SDL_ALPHA_OPAQUE);
	void get_rgb_from_color_code(Uint32 color_code, Uint8 *pred, Uint8 *pgreen, Uint8 *pblue, Uint8 *palpha=0);
	void draw_line(SDL_Point p1, SDL_Point p2, Uint32 color_code);
	/*
	 * about mixer
	 */
	bool load_sound(int sound_id, char *file_path) { return m_mixer.load_sound(sound_id, file_path); }
	bool load_music(char *file_path) { return m_mixer.load_music(file_path); }
	void play_sound(int sound_id, int num_of_loops) { m_mixer.play_sound(sound_id, num_of_loops); }
	void play_music(int num_of_loops) { m_mixer.play_music(num_of_loops); }
	void stop_sound(int sound_id) { m_mixer.stop_sound(sound_id); }
	void stop_all_sounds() { m_mixer.stop_all_sounds(); }
	void stop_music() { m_mixer.stop_music(); }
};


#endif /* SDLEnvironment_hpp */
