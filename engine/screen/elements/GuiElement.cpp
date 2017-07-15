#include "GuiElement.h"

void GuiElement::close(void)
{
    m_element_id = 0;
    m_parent_screen = NULL;
    m_dimensions = {0, 0, 0, 0};
    m_scaled_dimensions = {0, 0, 0, 0};
}

void GuiElement::resize(void)
{
    int scale_val = *get_parent_screen()->m_layout->get_scale_factor();
    SDL_Point *offset = get_parent_screen()->m_layout->get_content_origin();
    m_scaled_dimensions = SDL_Rect{offset->x + m_dimensions.x * scale_val, offset->y + m_dimensions.y * scale_val,
                                   m_dimensions.w * scale_val, m_dimensions.h * scale_val};
}

Screen *GuiElement::get_parent_screen()
{
    return m_parent_screen;
}

SDL_Rect *GuiElement::get_scaled_dimensions()
{
    return &m_scaled_dimensions;
}

SDL_Rect *GuiElement::get_dimensions()
{
    return &m_dimensions;
}

int GuiElement::get_id()
{
    return m_element_id;
}

void GuiElement::init(Screen *parent, SDL_Rect dim, int id)
{
    m_parent_screen = parent;
    m_dimensions = dim;
    m_scaled_dimensions = dim;
    m_element_id = id;
}

bool GuiElement::is_mouse_over(const int &x, const int &y)
{
    return x > get_scaled_dimensions()->x && x < get_scaled_dimensions()->x + get_scaled_dimensions()->w
           && y > get_scaled_dimensions()->y && y < get_scaled_dimensions()->y + get_scaled_dimensions()->h;
}