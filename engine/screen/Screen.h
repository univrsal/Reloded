/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"
#include "../core/Renderer.h"
#include "elements/GuiElement.h"
#include "Layout.h"
#include "../core/Tooltip.h"
#include <string.h>

class GuiElement;

class Renderer;

class Audio;

class Layout;

class Tooltip;

class Sfx;

class Screen
{
public:

    virtual void init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout, Audio* audio) = 0;

    virtual void draw_background(void) = 0;

    virtual void draw_foreground(void) = 0;

    virtual void close(void) = 0;

    virtual void action_performed(int action_id) = 0;

    virtual void set_active_tooltip(std::string *text, int x, int y) = 0;

    virtual Sfx *get_sfx_for_element(int element_type) = 0;

    Tooltip *m_tooltip;
	Audio* m_audio;
    SDL_Event *m_current_event;
    Renderer *m_renderer;
    Layout *m_layout;
};

#endif