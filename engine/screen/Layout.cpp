#include "Layout.h"

Layout::Layout(SDL_Window *game_window)
{
    m_game_window = game_window;
    m_content_w = DEFAULT_W;
    m_content_h = DEFAULT_H;
    resize();
}


Layout::~Layout()
{
}

void Layout::set_content_dim(uint16_t w, uint16_t h)
{
    m_content_w = w;
    m_content_h = h;
    resize();
}

void Layout::reset_content_dim(void)
{
    m_content_w = DEFAULT_W;
    m_content_h = DEFAULT_H;
    resize();
}

SDL_Rect *Layout::get_window_size(void)
{
    return &m_window_rect;
}

SDL_Rect *Layout::get_content_size(void)
{
    return &m_content_rect;
}

SDL_Point *Layout::get_content_origin(void)
{
    return &m_content_origin;
}

uint8_t *Layout::get_scale_factor(void)
{
    return &m_scale_factor;
}

void Layout::resize(void)
{
    SDL_GetWindowSize(m_game_window, &m_window_rect.w, &m_window_rect.h);

    int scale_w, scale_h;
    scale_w = m_window_rect.w / m_content_w;
    scale_h = m_window_rect.h / m_content_h;


    if (scale_w > 1 && scale_h > 1) {
        m_scale_factor = SDL_min(scale_h, scale_w);
    } else {
        m_scale_factor = 1;
    }

    m_content_rect.w = m_content_w * m_scale_factor;
    m_content_rect.h = m_content_h * m_scale_factor;

    m_content_rect.x = m_window_rect.w / 2 - m_content_rect.w / 2;
    m_content_rect.y = m_window_rect.h / 2 - m_content_rect.h / 2;

    m_content_origin = SDL_Point{m_content_rect.x, m_content_rect.y};
}