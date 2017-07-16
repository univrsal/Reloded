/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef LABEL_H
#define LABEL_H

#include "GuiElement.h"
#include <string>

class Label :
        public GuiElement
{
public:
    Label(int id, int x, int y, int w, int h, std::string *text, Screen *parent);

    Label(int id, SDL_Rect *dim, std::string *text, Screen *parent);

    ~Label();

	void close(void);

    void draw_background(void);

    void draw_foreground(void);

    void handle_event(SDL_Event *event);

    std::string *m_text;
};

#endif