/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "FontHelper.h"
#include "Palette.h"
#include "../Timer.h"
#include <stdio.h>
#include <iostream>
#include <string>

#define CONST_WINDOW_WIDTH 640
#define CONST_WINDOW_HEIGHT 400

#define CONST_FPS 60
#define CONST_TICKS_PER_FRAME 1000 / CONST_FPS

#define CONST_WINDOW_TITLE "Lode Runner: The Mad Monks' Revenge v0.1"

class GuiManager;

class FontHelper;

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

	void util_fill_rect_scaled(const SDL_Rect *r, const SDL_Color *color = NULL);

    void util_text_lode(std::string *text, int x, int y, const SDL_Color *color = NULL);

	void util_text_lode_shadow(std::string *text, int x, int y, const SDL_Color *color = NULL);

    void util_text_default(std::string *text, int x, int y, const SDL_Color *color = NULL);

    SDL_Rect util_text_default_dim(std::string *text, int type = FONT_ROBOTO);

    SDL_Renderer *m_sdl_renderer;
    SDL_Window *m_sdl_window;

    Palette *m_palette;
    GuiManager *m_gui_mgr;
    bool m_init_success;
private:
    TTF_Font *m_default_font;
    TTF_Font *m_lode_font;

    FontHelper *m_font_helper;
};

#endif