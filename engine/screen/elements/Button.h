/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "GuiElement.h"
#include "SDL.h"
#include "../../core/render/Texture.h"
#include "../../core/Tooltip.h"
#include "../../core/audio/Sfx.h"

class Button : public GuiElement
{
public:
    Button(int id, int type, int x, int y, const char *texure, const char *tooltip, Screen *parent);

    ~Button();

    void draw_background(void);

    void draw_foreground(void);

    void handle_event(SDL_Event *event);

    void close(void);

protected:

    Texture *m_bg;
    int m_type;
    bool m_pressed;
    bool m_tooltip_shown;
    std::string m_text;
    std::string m_tooltip;
    int m_hover_start;
};

#endif