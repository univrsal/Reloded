#include "Renderer.h"

Renderer::Renderer()
{
    m_sdl_renderer = NULL;
    m_sdl_window = NULL;
    m_init_success = true;
    m_default_font = NULL;
    m_palette = NULL;

}

Renderer::~Renderer()
{
    close();
    m_sdl_renderer = NULL;
    m_sdl_window = NULL;
    m_default_font = NULL;
    m_palette = NULL;
}

void Renderer::init(GuiManager *gui_mgr)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Initialization of SDL failed! Error: %s\n", SDL_GetError());
        m_init_success = false;
    }

    m_sdl_window = SDL_CreateWindow(CONST_WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    CONST_WINDOW_WIDTH, CONST_WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (m_sdl_window == NULL) {
        printf("Creating SDL Window failed! Error: %s\n", SDL_GetError());
        m_init_success = false;
    } else {
        SDL_SetWindowMinimumSize(m_sdl_window, CONST_WINDOW_WIDTH, CONST_WINDOW_HEIGHT);
        m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    if (m_sdl_renderer == NULL) {
        printf("Creating SDL Renderer failed! Error: %s\n", SDL_GetError());
        m_init_success = false;
    }

    if (TTF_Init() == -1) {
        printf("Initializing SDL_ttf failed! Error: %s\n", TTF_GetError());
        m_init_success = false;
    } else {
        m_default_font = new Font("./res/fnt/roboto.ttf");
        m_default_font->init();
    }

    m_gui_mgr = gui_mgr;
    m_palette = new Palette();
}

void Renderer::close(void)
{
    SDL_DestroyRenderer(m_sdl_renderer);
    SDL_DestroyWindow(m_sdl_window);
    m_palette->~Palette();
    TTF_Quit();
    SDL_Quit();
}

void Renderer::clear(void)
{
    util_set_color(m_palette->black());
    SDL_RenderClear(m_sdl_renderer);
}

void Renderer::repaint(void)
{
    SDL_RenderPresent(m_sdl_renderer);
}

void Renderer::util_set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_sdl_renderer, r, g, b, a);
}

void Renderer::util_set_color(const SDL_Color *color)
{
    if (color == NULL)
        util_set_color(m_palette->white()->r, m_palette->white()->g, m_palette->white()->b, m_palette->white()->a);
    else
        util_set_color(color->r, color->g, color->b, color->a);
}

void Renderer::util_draw_line(int x1, int y1, int x2, int y2, const SDL_Color *color)
{
    util_set_color(color);
    SDL_RenderDrawLine(m_sdl_renderer, x1, y1, x2, y2);
}

void Renderer::util_draw_line(const SDL_Point &p1, const SDL_Point &p2, const SDL_Color *color)
{
    util_set_color(color);
    SDL_RenderDrawLine(m_sdl_renderer, p1.x, p1.y, p2.x, p2.y);
}

void Renderer::util_draw_rect(const SDL_Rect *rect, const SDL_Color *color)
{
    util_set_color(color);
    SDL_RenderDrawRect(m_sdl_renderer, rect);
}

void Renderer::util_draw_rect(int x, int y, int w, int h, const SDL_Color *color)
{
    SDL_Rect *temp_rect = new SDL_Rect{x, y, w, h};
    util_set_color(color);
    SDL_RenderDrawRect(m_sdl_renderer, temp_rect);
    delete temp_rect;
}

void Renderer::util_fill_rect(const SDL_Rect *rect, const SDL_Color *color)
{
    util_set_color(color);
    SDL_RenderFillRect(m_sdl_renderer, rect);
}

void Renderer::util_fill_rect_shadow(const SDL_Rect *rect, const SDL_Color *color)
{
    SDL_Rect temp_rect = {rect->x + 3, rect->y + 3, rect->w, rect->h};
    SDL_Color temp_color = {0, 0, 0, 255};
    util_fill_rect(&temp_rect, &temp_color);
    util_fill_rect(rect, color);
}

void Renderer::util_fill_rect(int x, int y, int w, int h, const SDL_Color *color)
{
    util_set_color(color);
    SDL_Rect *temp_rect = new SDL_Rect{x, y, w, h};
    SDL_RenderFillRect(m_sdl_renderer, temp_rect);
    delete temp_rect;
}

void Renderer::util_draw_text(std::string *text, int x, int y)
{
    m_default_font->render_text(this, text, x, y);
}

void Renderer::util_draw_text(std::string *text, SDL_Rect *dest)
{
    m_default_font->render_text(this, text, dest);
}

void Renderer::util_draw_text_blended(std::string *text, int x, int y)
{
    m_default_font->render_text_blended(this, text, x, y);
}

SDL_Rect Renderer::util_get_text_dimensions(std::string *text, Font *font)
{
    if (font == NULL) {
        return m_default_font->get_text_dimension(this, text);
    } else {
        return font->get_text_dimension(this, text);
    }
}
