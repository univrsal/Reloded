#include "Texture.h"


Texture::Texture()
{
    m_sdl_texture = NULL;
}


Texture::Texture(const char *path, SDL_Renderer *renderer)
{
    m_sdl_texture = NULL;
    m_scale = NULL;
    load(path, renderer);
}

Texture::Texture(const char *path, SDL_Renderer *renderer, int *scale)
{
    m_sdl_texture = NULL;
    load(path, renderer);
    m_scale = scale;
}

Texture::~Texture()
{
    free();
    m_dimensions = {0, 0, 0, 0};
    m_scale = NULL;
}

void Texture::load(const char *path, SDL_Renderer *renderer)
{
    free();
    if (renderer == NULL)
        return;

    SDL_Surface *surface = IMG_Load(path);

    if (surface == NULL) {
        printf("ERROR: Couldn't load image %s! SDL_Error: %s, IMG_Error: %s\n", path, SDL_GetError(), IMG_GetError());
        return;
    }

    m_sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);

    m_dimensions.w = surface->w;
    m_dimensions.h = surface->h;
    SDL_FreeSurface(surface);
}

void Texture::free()
{
    if (m_sdl_texture != NULL)
        SDL_DestroyTexture(m_sdl_texture);
    m_sdl_texture = NULL;
}

void Texture::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, m_sdl_texture, NULL, NULL);
}

void Texture::draw_tiling(SDL_Renderer *renderer, SDL_Rect *target)
{
    int x_tiles, y_tiles;

    if (target->w % m_dimensions.w > 0)
        x_tiles = (target->w / m_dimensions.w) + 1;
    else
        x_tiles = target->w / m_dimensions.w;

    if (target->h % m_dimensions.h > 0)
        y_tiles = (target->h / m_dimensions.h) + 1;
    else
        y_tiles = target->h / m_dimensions.h;

    for (int x = 0; x < x_tiles; x++) {
        for (int y = 0; y < y_tiles; y++) {
            draw(renderer, x * m_dimensions.w, y * m_dimensions.h);
        }
    }
}

void Texture::draw(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect temp_rect = {x, y, m_dimensions.w, m_dimensions.h};

    if (m_scale != NULL) {
        temp_rect.w *= (int) (*m_scale);
        temp_rect.h *= (int) (*m_scale);
    }

    SDL_RenderCopy(renderer, m_sdl_texture, NULL, &temp_rect);
}

void Texture::draw(SDL_Renderer *renderer, SDL_Point *p)
{
    SDL_Rect temp_rect = {p->x, p->y, m_dimensions.w, m_dimensions.h};

    if (m_scale != NULL) {
        temp_rect.w *= (int) (*m_scale);
        temp_rect.h *= (int) (*m_scale);
    }

    SDL_RenderCopy(renderer, m_sdl_texture, NULL, &temp_rect);
}

void Texture::draw(SDL_Renderer *renderer, SDL_Point *p, int scaled_offset_x, int scaled_offset_y)
{
    SDL_Rect temp_rect = {p->x, p->y, m_dimensions.w, m_dimensions.h};

    if (m_scale != NULL) {
        temp_rect.w *= (int) (*m_scale);
        temp_rect.h *= (int) (*m_scale);
        temp_rect.x += scaled_offset_x * (int) (*m_scale);
        temp_rect.y += scaled_offset_y * (int) (*m_scale);
    }

    SDL_RenderCopy(renderer, m_sdl_texture, NULL, &temp_rect);
}

void Texture::draw(SDL_Renderer *renderer, SDL_Rect *target_dim, SDL_Rect *cutout)
{
    SDL_RenderCopy(renderer, m_sdl_texture, cutout, target_dim);
}
