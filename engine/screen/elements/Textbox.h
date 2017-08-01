/**
 * Created by universal on 8/1/17.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */


#ifndef RELODED_TEXTBOX_H
#define RELODED_TEXTBOX_H


#include "GuiElement.h"
#include <string>
#include "../../core/Resources.h"

class Textbox : public GuiElement
{
public:
    Textbox(int id, int x, int y, int w, int h, std::string text, Screen *parent);

    virtual ~Textbox();

    void close(void);

    void draw_background(void);

    void draw_foreground(void);

    void handle_events(SDL_Event *event);

private:
    std::string m_text;

    bool m_focused;
};


#endif //RELODED_TEXTBOX_H
