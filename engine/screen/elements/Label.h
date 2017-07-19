/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef LABEL_H
#define LABEL_H

#include "GuiElement.h"
#include "../Screen.h"
#include <string>

#define LABEL_TITLE 0
#define LABEL_GOLD 1
#define LABEL_WHITE 2

class Label :
        public GuiElement
{
public:
    Label(int id, int x, int y, int type, const char *text, Screen *parent);

    ~Label();

	void close(void);

    void draw_background(void);

    void draw_foreground(void);

    void handle_event(SDL_Event *event);

    std::string m_text;

    SDL_Color *m_color;
};

#endif