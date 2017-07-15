#include "Font.h"

Font::Font(const char *path)
{
    m_font_instance = NULL;
    m_font_path = path;
    m_size = FONT_DEFAULT;
    m_mode = FONT_SHADED;
    m_was_init = false;
    m_text_color = SDL_Color{0, 0, 0, 255};
}

Font::~Font()
{
    close();
}

void Font::set_size(int pt)
{
    if (!m_was_init)
        return;

    m_size = pt;
    TTF_CloseFont(m_font_instance);
    init();
}

void Font::close(void)
{
    TTF_CloseFont(m_font_instance);
    m_font_instance = NULL;
    m_font_path = NULL;
}

void Font::render_text(Renderer *render, std::string *text, int x, int y)
{
    SDL_Rect dim = SDL_Rect{x, y, 0, 0};
    m_mode = FONT_SHADED;
    render_text(render, text, &dim);
}

void Font::render_text(Renderer *render, std::string *text, SDL_Rect *dest)
{
    if (!m_was_init)
        return;

    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    switch (m_mode) {
        case FONT_SHADED:
            surface = TTF_RenderUTF8_Shaded(m_font_instance, text->c_str(), *render->m_palette->black(),
                                            *render->m_palette->white());
            break;
        case FONT_BLENDED:
            surface = TTF_RenderUTF8_Blended(m_font_instance, text->c_str(), m_text_color);
            break;
        default:
            break;
    }

    if (surface) {
        texture = SDL_CreateTextureFromSurface(render->m_sdl_renderer, surface);
        if (!texture) {
            printf("Error while creating texture from surface in text rendering! ERROR: %s\n", TTF_GetError());
        } else {
            dest->h = surface->h;
            dest->w = surface->w;

            SDL_RenderCopy(render->m_sdl_renderer, texture, NULL, dest);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    } else {
        printf("Error while creating surface from font in text rendering! ERROR: %s\n", TTF_GetError());
    }
}

void Font::render_text_blended(Renderer *renderer, std::string *text, int x, int y)
{
    m_mode = FONT_BLENDED;
    SDL_Rect dim = SDL_Rect{x, y, 0, 0};
    render_text(renderer, text, &dim);
}

void Font::render_text_blended(Renderer *renderer, std::string *text, int x, int y, int size)
{
    set_size(size);
    render_text_blended(renderer, text, x, y);
    set_size(FONT_DEFAULT);
}

SDL_Rect Font::get_text_dimension(Renderer *render, std::string *text, int size)
{
    if (!m_was_init)
        return SDL_Rect();

    if (size == -1)
        size = FONT_DEFAULT;

    SDL_Rect dest = {0, 0, 0, 0};
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = TTF_RenderUTF8_Shaded(m_font_instance, text->c_str(), m_text_color, *render->m_palette->white());

    if (surface) {
        texture = SDL_CreateTextureFromSurface(render->m_sdl_renderer, surface);
        if (!texture) {
            printf("Error while creating texture from surface in text rendering! ERROR: %s\n", TTF_GetError());
        } else {
            dest.h = surface->h;
            dest.w = surface->w;
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    } else {
        printf("Error while creating surface from font in text rendering! ERROR: %s\n", TTF_GetError());
    }
    return dest;
}

void Font::init()
{
    m_font_instance = TTF_OpenFont(m_font_path, m_size);
    if (!m_font_instance) {
        printf("TTF_Open font (%s) error: %s // %s\n", m_font_path, TTF_GetError(), SDL_GetError());
    } else {
        m_was_init = true;
    }
}
