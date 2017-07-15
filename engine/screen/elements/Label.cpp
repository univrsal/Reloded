#include "Label.h"

Label::Label(int id, int x, int y, int w, int h, std::string *text, Screen *parent)
{
    m_dimensions = SDL_Rect {x, y, w, h};
    m_text = text;
    m_parent_screen = parent;
    m_element_id = id;
}

Label::Label(int id, SDL_Rect *dim, std::string *text, Screen *parent)
{
    m_dimensions = *dim;
    m_text = text;
    m_parent_screen = parent;
    m_element_id = id;
}

Label::~Label()
{
    close();
}

void Label::draw_background(void)
{
    m_parent_screen->m_renderer->util_draw_text(m_text, &m_dimensions);
}

void Label::handle_event(SDL_Event *event)
{

}