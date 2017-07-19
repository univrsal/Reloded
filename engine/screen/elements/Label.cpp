#include "Label.h"

Label::Label(int id, int x, int y, int type, const char *text, Screen *parent)
{
    m_dimensions = SDL_Rect {x, y, 0, 0};
    m_text = std::string(text);
    m_parent_screen = parent;
    m_element_id = id;
    switch (type) {
        default:
        case LABEL_GOLD:
            m_color = parent->m_renderer->m_palette->get_accent();
            break;
        case LABEL_TITLE:
            m_color = parent->m_renderer->m_palette->black();
            break;
        case LABEL_WHITE:
            m_color = parent->m_renderer->m_palette->white();
            break;
    }
}

Label::~Label()
{
    close();
    m_text.clear();
}

void Label::close(void)
{
}

void Label::draw_background(void)
{
    SDL_Point *o = m_parent_screen->m_layout->get_content_origin();
    int scale = *m_parent_screen->m_layout->get_scale_factor();

    m_parent_screen->m_renderer->util_text_lode(&m_text, o->x + m_dimensions.x * scale, o->y + m_dimensions.y * scale,
                                                m_color);
}

void Label::handle_event(SDL_Event *event)
{

}

void Label::draw_foreground(void)
{

}
