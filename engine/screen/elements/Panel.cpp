//
// Created by usr on 8/28/17.
//

#include "Panel.h"

Panel::Panel(int8_t id, int x, int y,  int w, int h, const char *tooltip, Screen *parent)
{
    SDL_Rect temp = { x, y, w, h };
    m_tooltip = std::string(tooltip);
    m_element_id = id;
    m_hover_start = 0;
    m_tooltip_shown = false;
    m_hovered = false;
    m_texture = NULL;
    init(parent, temp, id);
}

Panel::Panel(int8_t id, int x, int y, int w, int h, const char *tooltip, const char *texture, Screen *parent)
{
    SDL_Rect temp = { x, y, w, h };
    m_tooltip = std::string(tooltip);
    m_element_id = id;
    m_hover_start = 0;
    m_tooltip_shown = false;
    m_hovered = false;

    init(parent, temp, id);
    m_texture = new Texture(texture, get_resources()->sdl_renderer(), get_resources()->scalef());
}


Panel::~Panel()
{
    close();
    delete m_texture;

    m_texture = NULL;
}

void Panel::close(void)
{
    if (m_texture)
    {
        m_texture->free();
    }
}

void Panel::draw_background(void)
{
    if (m_texture)
        m_texture->draw(get_resources()->sdl_renderer(), m_dimensions.x, m_dimensions.y);

    if (!m_tooltip_shown && !m_tooltip.empty() && m_hover_start != 0 && SDL_GetTicks() - m_hover_start > 1000)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        m_parent_screen->set_active_tooltip(&m_tooltip, x + 15, y);
        m_tooltip_shown = true;
    }
}

void Panel::draw_foreground(void)
{

}

void Panel::handle_events(SDL_Event *event)
{
    m_hovered = is_mouse_over_scaled(event->button.x, event->button.y);

    if (!m_tooltip.empty() && m_hovered)
    {
        if (m_hover_start == 0)
        {
            m_hover_start = SDL_GetTicks();
        }
    }
    else
    {
        if (m_hover_start != 0)
        {
            m_hover_start = 0;
            get_parent_screen()->set_active_tooltip(NULL, 0, 0);
            m_tooltip_shown = false;
        }
    }
}

