/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include "SDL.h"
#include <stdio.h>

#define DEFAULT_W 640
#define DEFAULT_H 400

class Layout
{
public:
    Layout(SDL_Window *game_window);

    ~Layout();

	SDL_Rect *get_window_size(void);

	SDL_Rect *get_content_size(void);

	SDL_Point *get_content_origin(void);

	uint8_t *get_scale_factor(void);

	void set_content_dim(uint16_t w, uint16_t h);

	void reset_content_dim(void);

	void resize(void);

private:
	uint16_t m_content_w;
	uint16_t m_content_h;

    uint8_t m_scale_factor;
    SDL_Window *m_game_window;
    SDL_Point m_content_origin;
    SDL_Rect m_window_rect;
    SDL_Rect m_content_rect;
};

#endif