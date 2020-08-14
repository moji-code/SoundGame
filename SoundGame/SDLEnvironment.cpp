//
//  SDLEnvironment.cpp
//
//  Created by mojito on 2020/05/01.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "SDLEnvironment.hpp"

SDLEnvironment::SDLEnvironment()
{
	m_magnification = 1;
	m_sdl_initialized = false;
	m_img_initialized = false;
	m_mix_initialized = false;
	m_pwindow = 0;
	m_prenderer = 0;
	m_window_width = m_window_height = -1;
}

SDLEnvironment::~SDLEnvironment()
{
	// destroy renderer if it exists
	if (m_prenderer != 0)
	{
		SDL_DestroyRenderer(m_prenderer);
		m_prenderer = 0;
	}
	
	// destroy window if it exists
	if (m_pwindow != 0) {
		SDL_DestroyWindow(m_pwindow);
		m_pwindow = 0;
	}
	
	// quit mixer library
	if (m_mix_initialized == true)
	{
		Mix_Quit();
	}

	// quit img library
	if (m_img_initialized == true) {
		IMG_Quit();
	}
	
	// finally quit SDL
	if (m_sdl_initialized == true) {
		SDL_Quit();
	}
}

/*
 * initialize SDL
 * return true on success
 */
bool SDLEnvironment::init(float magnification)
{
	// initialize SDL
	int ret = SDL_Init(SDL_INIT_EVERYTHING);

	if (ret == 0) {
		m_magnification = magnification;
		m_sdl_initialized = true;
	} else {
		printf("could not init SDL: %s\n", SDL_GetError());
		m_sdl_initialized = false;
		return false;
	}

	// initialize IMG
	int img_flags = IMG_INIT_PNG;
	ret = IMG_Init(img_flags);
	if (ret == img_flags) {
		m_img_initialized = true;
	} else {
		printf("could not init IMG: %s\n", SDL_GetError());
		m_img_initialized = false;
		return false;
	}

	// initialize MIX
	/*
	int mix_flags = MIX_INIT_MP3;
	ret = Mix_Init(mix_flags);
	 */
	bool scceeded = m_mixer.init(MIX_INIT_MP3);
	if (scceeded == true)
	{
		m_mix_initialized = true;
	}
	else{
		printf("could not init MIX: %s\n", SDL_GetError());
		m_mix_initialized = false;
		return false;
	}
	
	return true;
}

/*
 * create a new window
 */
bool SDLEnvironment::create_window(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	int new_w = int(w * m_magnification);
	int new_h = int(h * m_magnification);
	
	if (m_pwindow != 0) {
		return false;
	}
	m_pwindow = SDL_CreateWindow(title, x,y, new_w,new_h, flags);
	
	if (m_pwindow == NULL) {
		return false;
	}

	m_window_width = w;
	m_window_height = h;
	
	// create & save window's renderer
	m_prenderer = SDL_CreateRenderer(m_pwindow, -1, SDL_RENDERER_ACCELERATED);
	
	return true;
}

bool SDLEnvironment::create_window(const char* title, int w, int h)
{
	return create_window(title,
						 SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED,
						 w, h,
						 SDL_WINDOW_OPENGL);
}


/*
 * get window surface
 */
/*
SDL_Surface *SDLEnvironment::get_window_surface()
{
	if (m_pwindow != 0) {
		return SDL_GetWindowSurface(m_pwindow);
	}
	return NULL;
}
*/

/*
 * update window surface
 * MOD: to use SDL_Renderer instead of SDL_Surface
 */
void SDLEnvironment::update_window()
{
	SDL_RenderPresent(get_window_renderer());
	
	// the following code is the old version that uses SDL_Surface
	/*
	if (m_pwindow != NULL) {
		SDL_UpdateWindowSurface(m_pwindow);
	}
	 */
}

/*
 * blit image using m_magnification and ratio
 */
void SDLEnvironment::blit_image(SDL_Surface *image, SDL_Rect *src, int dest_x, int dest_y, double ratio)
{
	SDL_Texture *ptexture = SDL_CreateTextureFromSurface(get_window_renderer(), image);
	//	SDL_Surface *dest_surface = get_window_surface();

	SDL_Rect dest;
	dest.x = dest_x * m_magnification;
	dest.y = dest_y * m_magnification;
	if (src != NULL) {
		dest.w = src->w * m_magnification * ratio;
		dest.h = src->h * m_magnification * ratio;
	} else {
		dest.w = image->w * m_magnification * ratio;
		dest.h = image->h * m_magnification * ratio;
	}

	SDL_RenderCopy(get_window_renderer(), ptexture, src, &dest);
//	SDL_BlitScaled(image, src, dest_surface, &dest);
	
	SDL_DestroyTexture(ptexture);
}

void SDLEnvironment::blit_image(SDL_Texture *ptexture, SDL_Rect *src, int dest_x, int dest_y, double ratio)
{
	SDL_Rect dest;
	dest.x = dest_x * m_magnification;
	dest.y = dest_y * m_magnification;
	if (src != NULL) {
		dest.w = src->w * m_magnification * ratio;
		dest.h = src->h * m_magnification * ratio;
	} else {
		Uint32 src_format;
		int src_access;
		int src_width, src_height;
		SDL_QueryTexture(ptexture, &src_format, &src_access, &src_width, &src_height);
		dest.w = src_width  * m_magnification * ratio;
		dest.h = src_height * m_magnification * ratio;
	}

	SDL_RenderCopy(get_window_renderer(), ptexture, src, &dest);
}

/*
 * fill rectangle with specified color
 * MOD: use SDL_RenderFillRect instead of SDL_FillRect with SDL_Surface
 */
void SDLEnvironment::fill_rect(SDL_Rect rect, Uint32 color_code)
{
	// spreds rectangle
	rect.x *= m_magnification;
	rect.y *= m_magnification;
	rect.w *= m_magnification;
	rect.h *= m_magnification;
	
//	SDL_FillRect(get_window_surface(), &rect, color_code);

	// set render color
	Uint8 red, green, blue, alpha;
	get_rgb_from_color_code(color_code, &red, &green, &blue, &alpha);
	SDL_SetRenderDrawColor(get_window_renderer(), red, green, blue, alpha);
	
	// fill rect
	SDL_RenderFillRect(get_window_renderer(), &rect);
}

// MOD: create original rgb format (RRGGBBAA: RR = 1 byte)
//		to use SDL_Renderer instead of SDL_Surface
Uint32 SDLEnvironment::get_color_code_from_rgb(int red, int green, int blue, int alpha)
{
	// following 1 line is old version
//	return SDL_MapRGB(get_window_surface()->format, red, green, blue);

	Uint32 color_code = 0;
	
	color_code = red;

	color_code <<= 8;
	color_code |= green;

	color_code <<= 8;
	color_code |= blue;

	color_code <<= 8;
	color_code |= alpha;
	
	return color_code;
}

void SDLEnvironment::get_rgb_from_color_code(Uint32 color_code, Uint8 *pred, Uint8 *pgreen, Uint8 *pblue, Uint8 *palpha)
{
	if (*palpha != 0)
	{
		*palpha = color_code & 0xff;
	}
	
	color_code >>= 8;
	*pblue = color_code & 0xff;
	
	color_code >>= 8;
	*pgreen = color_code & 0xff;
	
	color_code >>= 8;
	*pred = color_code & 0xff;
}


/*
 * draw line with specified color
 */
void SDLEnvironment::draw_line(SDL_Point p1, SDL_Point p2, Uint32 color_code)
{
	// apply magnification
	p1.x *= m_magnification;
	p1.y *= m_magnification;
	p2.x *= m_magnification;
	p2.y *= m_magnification;
	
	// prepare RGB
	Uint8 red, green, blue, alpha;
	get_rgb_from_color_code(color_code, &red, &green, &blue, &alpha);

	// get SDL renderer
	SDL_Renderer *prenderer = get_window_renderer();

	// set render colode
	SDL_SetRenderDrawColor(prenderer, red, green, blue, alpha);
	
	// draw the line(s)
	switch (get_slope(p1, p2))
	{
		case horizontal:
			for (int i = 0; i < m_magnification; i++)
			{
				SDL_RenderDrawLine(prenderer,
								   p1.x, p1.y + i,
								   p2.x, p2.y + i);
			}
			break;
			
		case vertical:
			for (int i = 0; i < m_magnification; i++)
			{
				SDL_RenderDrawLine(prenderer,
								   p1.x + i, p1.y,
								   p2.x + i, p2.y);
			}
			break;
	}
}

// calc slope
// like / and \ -> vertical		|dy/dx| > 1
// like -		-> horizontal	|dy/dx| < 1
int SDLEnvironment::get_slope(SDL_Point p1, SDL_Point p2)
{
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	
	if (dx == 0)
	{
		return vertical;
	}
	
	int slope = abs(dy/dx);
	if (slope <= 1)
	{
		return horizontal;
	}
	
	return vertical;
}
