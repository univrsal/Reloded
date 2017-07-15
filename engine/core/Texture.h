/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

class Texture
{
public:
    Texture(const char *path, SDL_Renderer *renderer);

    Texture(const char *path, SDL_Renderer *renderer, int *scale);

    Texture();

    ~Texture();

    void load(const char *path, SDL_Renderer *renderer);

    void free();

    void draw(SDL_Renderer *renderer);

    void draw_tiling(SDL_Renderer *renderer, SDL_Rect *target);

    void draw(SDL_Renderer *renderer, int x, int y);

    void draw(SDL_Renderer *renderer, SDL_Point *p);

    void draw(SDL_Renderer *renderer, SDL_Point *p, int scaled_offset_x, int scaled_offset_y);

    void draw(SDL_Renderer *renderer, SDL_Rect *target_dim, SDL_Rect *cutout);

private:
    SDL_Texture *m_sdl_texture;
    SDL_Rect m_dimensions;
    int *m_scale;
};

