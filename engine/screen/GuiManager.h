#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "Screen.h"
#include "menus/GameScreen.h"
#include "menus/SpSetupScreen.h"
#include "../util/Textures.h"
#include "../core/Input.h"
#include "Layout.h"

#define GUI_NONE -1
#define GUI_GAME 0
#define GUI_SP 1

class Screen;

class Layout;

class Texture;

class Input;

class GuiManager
{
public:
    GuiManager();

    ~GuiManager();

    void init(Input *input, Renderer *renderer);

    void draw_gui(void);

    Screen *get_active_screen();

    void set_screen(Uint8 gui_id);

    Texture *m_bg;
    Renderer *m_renderer;
    Screen *m_current_screen;
    Input *m_input;
    Layout *m_layout;
};

#endif