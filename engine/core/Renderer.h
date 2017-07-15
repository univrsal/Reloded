/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "Font.h"
#include "Palette.h"
#include "Timer.h"
#include <stdio.h>
#include <iostream>
#include <string>

#define CONST_WINDOW_WIDTH 640
#define CONST_WINDOW_HEIGHT 400

#define CONST_FPS 30
#define CONST_TICKS_PER_FRAME 1000 / CONST_FPS

#define CONST_WINDOW_TITLE "Lode Runner: The Mad Monks' Revenge v0.1"

class Font;

class GuiManager;

class Renderer
{
public:
    Renderer();

    ~Renderer();

    void init(GuiManager *gui_mgr);

    void close(void);

    void clear(void);

    void repaint(void);

    void util_set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void util_set_color(const SDL_Color *color);

    void util_draw_line(int x1, int y1, int x2, int y2, const SDL_Color *color = NULL);

    void util_draw_line(const SDL_Point &p1, const SDL_Point &p2, const SDL_Color *color = NULL);

    void util_draw_rect(const SDL_Rect *rect, const SDL_Color *color = NULL);

    void util_draw_rect(int x, int y, int w, int h, const SDL_Color *color = NULL);

    void util_fill_rect(const SDL_Rect *rect, const SDL_Color *color = NULL);

    void util_fill_rect_shadow(const SDL_Rect *rect, const SDL_Color *color = NULL);

    void util_fill_rect(int x, int y, int w, int h, const SDL_Color *color = NULL);

    void util_draw_text(std::string *text, int x, int y);

    void util_draw_text(std::string *text, SDL_Rect *dest);

    void util_draw_text_blended(std::string *text, int x, int y);

    SDL_Rect util_get_text_dimensions(std::string *text, Font *font = NULL);

    SDL_Renderer *m_sdl_renderer;
    SDL_Window *m_sdl_window;

    Palette *m_palette;
    Font *m_default_font;
    GuiManager *m_gui_mgr;
    bool m_init_success;
};

#endif