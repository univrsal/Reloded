/**
 * Created by universallp on 28.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef RELODED_PANEL_H
#define RELODED_PANEL_H

#include "GuiElement.h"
#include "../../core/render/Texture.h"
#include "../../core/Resources.h"
#include "../Screen.h"
#include <string>



class Panel :
        public GuiElement
{
public:
    Panel(int8_t id, int x, int y, int w, int h, const char *tooltip, Screen *parent);

    Panel(int8_t id, int x, int y, int w, int h, const char *tooltip, const char *texture, Screen *parent);

    ~Panel();

    void close(void);

    void draw_background(void);

    void draw_foreground(void);

    void handle_events(SDL_Event *event);

private:
    std::string m_tooltip;
    int m_hover_start;
    bool m_hovered;
    bool m_tooltip_shown;
    Texture* m_texture;
};


#endif //RELODED_PANEL_H
