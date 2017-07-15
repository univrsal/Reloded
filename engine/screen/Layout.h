#ifndef LAYOUT_H
#define LAYOUT_H

#include "SDL.h"
#include <stdio.h>

#define LAYOUT_CONTENT_W 640
#define LAYOUT_CONTENT_H 400

class Layout
{
public:
    Layout(SDL_Window *game_window);

    ~Layout();

    SDL_Rect *get_window_size();

    SDL_Rect *get_content_size();

    SDL_Point *get_content_origin();

    int *get_scale_factor();

    void resize();

private:
    int m_scale_factor;
    SDL_Window *m_game_window;
    SDL_Point m_content_origin;
    SDL_Rect m_window_rect;
    SDL_Rect m_content_rect;
};

#endif