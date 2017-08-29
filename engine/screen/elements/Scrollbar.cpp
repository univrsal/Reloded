/**
 * Created by universallp on 02.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "Scrollbar.h"

Scrollbar::Scrollbar(int8_t id, int x, int y, int h, int max, uint8_t type, Screen *parent)
{
    m_type = type;
    SDL_Rect temp_rect;

    switch (type)
    {
        default:
        case SCROLL_TYPE_DIALOG:
            temp_rect = {x, y, 10, h};
            m_scroll_button_dim = {x, y, 10, 0};
            set_bar_height(0.5f);
            m_scroll_body = NULL;
            m_scroll_btn = NULL;
            m_scroll_button_dim_scaled = {};
            break;
        case SCROLL_TYPE_INGAME:
            temp_rect = {x, y, 15, h};
            m_scroll_button_dim = {x, y, 15, 14};
            m_scroll_button_dim_scaled = parent->m_resources->util_scale_rect(&m_scroll_button_dim,
                                                                              *parent->m_resources->scalef());
            m_scroll_body = new Texture(CONST_PATH_BTN_SCROLL_BODY, parent->m_resources->sdl_renderer(),
                                        parent->m_resources->scalef());
            m_scroll_btn = new Texture(CONST_PATH_BTN_SCROLL_BTN, parent->m_resources->sdl_renderer(),
                                       parent->m_resources->scalef());
            break;
    }

    init(parent, temp_rect, id);
    resize();
    m_progress = 0;
    m_max_scroll = (uint16_t) max;
    m_scroll_handle_used = false;
}

Scrollbar::~Scrollbar()
{
    close();
}

void Scrollbar::set_bar_height(float f)
{
    m_scroll_button_dim.h = (int) (m_dimensions.h * f);
}

void Scrollbar::draw_background(void)
{
    switch (m_type)
    {
        default:
        case SCROLL_TYPE_DIALOG:
            get_resources()->renderer()->util_fill_rect(get_dimensions(), get_resources()->palette()->gray());
            break;
        case SCROLL_TYPE_INGAME:

            m_scroll_body->draw_tiling_scaled(get_resources()->sdl_renderer(), get_scaled_dimensions());
            break;
    }
}

void Scrollbar::draw_foreground(void)
{
    GuiElement::draw_foreground();
    switch (m_type)
    {
        default:
        case SCROLL_TYPE_DIALOG:
            get_resources()->renderer()->util_fill_rect(&m_scroll_button_dim, get_resources()->palette()->dark_gray());
            break;
        case SCROLL_TYPE_INGAME:
            m_scroll_btn->draw(get_resources()->sdl_renderer(), m_scroll_button_dim_scaled.x,
                               m_scroll_button_dim_scaled.y);
            break;
    }
}

void Scrollbar::handle_events(SDL_Event *e)
{
    if (e->type == SDL_MOUSEWHEEL)
    {
        if (e->wheel.y > 0)
        {
            scroll(SCROLL_UP);
        }
        else
        {
            scroll(SCROLL_DOWN);
        }
    }
    else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
    {
        bool flag = get_resources()->util_is_in_rect(get_handle_dim(), e->button.x, e->button.y);
        if (flag && !m_scroll_handle_used)
        {
            m_scroll_handle_offset = (uint16_t) (e->button.y - (get_handle_dim()->y));
        }

        m_scroll_handle_used = flag;
    }
    else if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT)
    {
        m_scroll_handle_used = false;
    }
    else if (e->type == SDL_MOUSEMOTION)
    {
        if (m_scroll_handle_used)
        {
            int t = e->button.y - get_dimensions()->y - m_scroll_handle_offset;
            set_progress(((float) t) / (get_dimensions()->h - m_scroll_button_dim.h));
        }
    }
}

void Scrollbar::scroll(bool dir)
{
    if (dir)
    {
        m_progress = (uint16_t) SDL_min(m_max_scroll, m_progress + 1);
    }
    else
    {
        m_progress = (uint16_t) SDL_max(0, m_progress - 1);
    }
    m_scroll_button_dim.y = (int) (get_dimensions()->y +
                                   (get_dimensions()->h - m_scroll_button_dim.h) * get_progress());
    resize();
}

void Scrollbar::set_max(int max)
{
    m_max_scroll = (uint16_t) max;
}

void Scrollbar::start_pos(void)
{
    m_scroll_button_dim.y = get_dimensions()->y;
    m_progress = 0;
    resize();
}

void Scrollbar::end_pos(void)
{
    m_progress = m_max_scroll;
    m_scroll_button_dim.y = (int) (get_dimensions()->y +
                                   (get_dimensions()->h - m_scroll_button_dim.h) * get_progress());
    resize();
}

void Scrollbar::set_pos(const int & x, const int & y)
{
    m_scroll_button_dim.x = x;
    int old_y_pos = m_scroll_button_dim.y - get_dimensions()->y;
    GuiElement::set_pos(x, y);
    m_scroll_button_dim.y = y + old_y_pos;
}

float Scrollbar::get_progress(void)
{
    return m_max_scroll == 0 ? 0.f : ((float) m_progress) / m_max_scroll;
}

void Scrollbar::close(void)
{
    m_scroll_button_dim = {};
    m_scroll_button_dim_scaled = {};
}

uint16_t Scrollbar::get_offset(void)
{
    return m_progress;
}

void Scrollbar::set_progress(float f)
{
    m_progress = (uint16_t) SDL_max(SDL_min((m_max_scroll * f), m_max_scroll), 0);
    m_scroll_button_dim.y = (int) (get_dimensions()->y +
                                   (get_dimensions()->h - m_scroll_button_dim.h) * get_progress());
    resize();
}

void Scrollbar::resize(void)
{
    GuiElement::resize();
    if (m_type == SCROLL_TYPE_INGAME)
    {
        m_scroll_button_dim_scaled = get_resources()->util_scale_rect(&m_scroll_button_dim, *get_resources()->scalef());
    }
}

SDL_Rect *Scrollbar::get_handle_dim(void)
{
    return m_type == SCROLL_TYPE_DIALOG ? &m_scroll_button_dim : &m_scroll_button_dim_scaled;
}

SDL_Rect *Scrollbar::get_body_dim(void)
{
    return m_type == SCROLL_TYPE_DIALOG ? &m_dimensions : &m_scaled_dimensions;
}

