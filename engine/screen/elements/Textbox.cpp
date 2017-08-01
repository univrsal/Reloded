/**
 * Created by universal on 8/1/17.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */


#include "Textbox.h"

Textbox::Textbox(int id, int x, int y, int w, int h, std::string text, Screen *parent)
{
    m_dimensions = SDL_Rect {x, y, w, h};
    m_text = std::string(text);
    m_parent_screen = parent;
    m_element_id = id;
    m_focused = false;
}

Textbox::~Textbox()
{
    close();
}

void Textbox::close(void)
{
    GuiElement::close();
    m_text.clear();
    m_focused = false;
}

void Textbox::draw_foreground(void)
{
    if (m_text.size() > 0)
        get_resources()->renderer()->util_text_default(&m_text, m_dimensions.x, m_dimensions.y,
                                                       get_resources()->palette()->white());
}

void Textbox::draw_background(void)
{
    get_resources()->renderer()->util_fill_rect(&m_dimensions, get_resources()->palette()->dark_gray());
    get_resources()->renderer()->util_draw_rect(&m_dimensions, get_resources()->palette()->black());
}

void Textbox::handle_events(SDL_Event *event)
{

}

