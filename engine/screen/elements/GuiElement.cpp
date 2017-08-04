/**
* Created by universallp on 14.07.2017.
* This file is part of reloded which is licenced
* under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
* github.com/univrsal/reloded
*/

#include "GuiElement.h"
#include "../../core/Resources.h"

GuiElement::~GuiElement()
{
	close();
	m_parent_screen = NULL;
}

void GuiElement::close(void)
{
    m_element_id = 0;
    m_dimensions = {0, 0, 0, 0};
    m_scaled_dimensions = {0, 0, 0, 0};
}

void GuiElement::resize(void)
{
    int scale_val = *get_resources()->scalef();
    SDL_Point *offset = get_resources()->origin();
    m_scaled_dimensions = SDL_Rect{offset->x + m_dimensions.x * scale_val, offset->y + m_dimensions.y * scale_val,
                                   m_dimensions.w * scale_val, m_dimensions.h * scale_val};
}

Screen *GuiElement::get_parent_screen()
{
    return m_parent_screen;
}

Resources * GuiElement::get_resources()
{
	return get_parent_screen()->m_resources;
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

bool GuiElement::is_mouse_over_scaled(const int &x, const int &y)
{
    return x > get_scaled_dimensions()->x && x < get_scaled_dimensions()->x + get_scaled_dimensions()->w
        && y > get_scaled_dimensions()->y && y < get_scaled_dimensions()->y + get_scaled_dimensions()->h;
}

bool GuiElement::is_mouse_over(const int & x, const int & y)
{
	return x > get_dimensions()->x && x < get_dimensions()->x + get_dimensions()->w
		&& y > get_dimensions()->y && y < get_dimensions()->y + get_dimensions()->h;
}

void GuiElement::set_pos(const int& x, const int& y)
{
    m_dimensions.x = x;
    m_dimensions.y = y;
}
