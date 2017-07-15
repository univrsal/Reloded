#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <stdio.h>
#include "SDL.h"
#include "../Screen.h"
#include "../../core/Input.h"
#include "../elements/Label.h"
#include "../elements/Button.h"
#include "../../core/Texture.h"
#include "../../util/Textures.h"
#include "../../util/Lang.h"
#include "../../core/audio/Sfx.h"
#include "../../util/Sounds.h"
#include "../GuiManager.h"
#include <vector>
#include <memory>

class Screen;

class Renderer;

class GameScreen : public Screen
{
public:
    GameScreen();

    ~GameScreen();

    void draw_background(void);

    void draw_foreground(void);

    void init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout);

    void set_active_tooltip(std::string *text, int x, int y);

    Sfx *get_sfx_for_element(int element_type);

    void action_performed(int action_id);

    void close(void);

private:
    std::vector<std::unique_ptr<GuiElement>> m_screen_elements;
    Texture *m_border;
    Texture *m_logo;

    Sfx *m_rock;
    Sfx *m_soft_rock;
};

#endif