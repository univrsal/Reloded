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

    void draw_background(void);

    void handle_event(SDL_Event *event);

    std::string *m_text;
};

#endif