/**
 * Created by universal on 8/1/17.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */


#include "Textbox.h"

Textbox::Textbox(int8_t id, int x, int y, int w, int h, std::string text, Screen *parent)
{
    m_dimensions = SDL_Rect {x, y, w, h};
    m_parent_screen = parent;
    set_text(text);
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
    m_cut_text.clear();
    m_focused = false;
}

void Textbox::draw_foreground(void)
{
    GuiElement::draw_foreground();

    if (m_cut_text.size() > 0)
        get_resources()->renderer()->util_text_default(&m_cut_text, m_dimensions.x + 2, m_dimensions.y + 2,
                                                       get_resources()->palette()->black());
}

void Textbox::draw_background(void)
{
    get_resources()->renderer()->util_fill_rect(&m_dimensions, get_resources()->palette()->gray());
    get_resources()->renderer()->util_draw_rect(&m_dimensions, get_resources()->palette()->black());
}

void Textbox::handle_events(SDL_Event *event)
{

}

void Textbox::set_text(std::string s)
{
    m_text = s;
    m_cut_text = m_text;
    get_resources()->util_cut_string(m_cut_text, get_dimensions()->w - 22, false);
}

