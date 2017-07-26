/**
 * Created by universal on 19.07.17.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "FontHelper.h"

FontHelper::FontHelper(Renderer *renderer)
{
    m_renderer = renderer;
    m_mode = FONT_BLENDED;
}

FontHelper::~FontHelper()
{
    m_renderer = NULL;
}

void
FontHelper::draw(std::string *text, int x, int y, TTF_Font *font, const SDL_Color *fg, const SDL_Color *bg, int scale)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    switch (m_mode) {
        default:
        case FONT_BLENDED:
            surface = TTF_RenderUTF8_Blended(font, text->c_str(), *fg);
            break;
        case FONT_SHADED:
            surface = TTF_RenderUTF8_Shaded(font, text->c_str(), *fg, *bg);
            break;
    }

    if (surface) {
        texture = SDL_CreateTextureFromSurface(m_renderer->m_sdl_renderer, surface);

        if (texture) {
            SDL_Rect dest = {x, y, surface->w * scale, surface->h * scale};
            SDL_RenderCopy(m_renderer->m_sdl_renderer, texture, NULL, &dest);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        } else {
            printf("Error while creating texture from surface in text rendering! ERROR: %s\n", TTF_GetError());
        }
    } else {
        printf("Error while creating surface from font in text rendering! ERROR: %s\n", TTF_GetError());
    }
}

void FontHelper::set_mode(int m)
{
    m_mode = m;
}

void FontHelper::draw(std::string *text, int x, int y, TTF_Font *font, int scale)
{
    draw(text, x, y, font, m_renderer->m_palette->black(), m_renderer->m_palette->white(), scale);
}

SDL_Rect FontHelper::get_text_dimension(TTF_Font *font, std::string *text, int scale)
{
    SDL_Surface *surface = NULL;
    surface = TTF_RenderUTF8_Shaded(font, text->c_str(), *m_renderer->m_palette->black(),
                                    *m_renderer->m_palette->white());
    SDL_Rect dest = {};

    if (surface) {
        dest.w = surface->w;
        dest.h = surface->h;
    } else {
        printf("Error while creating surface from font in text rendering! ERROR: %s\n", TTF_GetError());
    }
    return dest;
}

void FontHelper::draw(std::string *text, int x, int y, TTF_Font *font, const SDL_Color *fg, int scale)
{
    set_mode(FONT_BLENDED);
    draw(text, x, y, font, fg, NULL, scale);
}
