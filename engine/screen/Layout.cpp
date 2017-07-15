#include "Layout.h"

Layout::Layout(SDL_Window *game_window)
{
    m_game_window = game_window;
    resize();
}


Layout::~Layout()
{
    m_game_window = NULL;
}

SDL_Rect *Layout::get_window_size()
{
    return &m_window_rect;
}

SDL_Rect *Layout::get_content_size()
{
    return &m_content_rect;
}

SDL_Point *Layout::get_content_origin()
{
    return &m_content_origin;
}

int *Layout::get_scale_factor()
{
    return &m_scale_factor;
}

void Layout::resize()
{
    SDL_GetWindowSize(m_game_window, &m_window_rect.w, &m_window_rect.h);

    int scale_w, scale_h;
    scale_w = m_window_rect.w / LAYOUT_CONTENT_W;
    scale_h = m_window_rect.h / LAYOUT_CONTENT_H;


    if (scale_w > 1 && scale_h > 1) {
        m_scale_factor = SDL_min(scale_h, scale_w);
    } else {
        m_scale_factor = 1;
    }

    m_content_rect.w = LAYOUT_CONTENT_W * m_scale_factor;
    m_content_rect.h = LAYOUT_CONTENT_H * m_scale_factor;

    m_content_rect.x = m_window_rect.w / 2 - m_content_rect.w / 2;
    m_content_rect.y = m_window_rect.h / 2 - m_content_rect.h / 2;

    m_content_origin = SDL_Point{m_content_rect.x, m_content_rect.y};
}