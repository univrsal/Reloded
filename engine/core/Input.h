#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include "../screen/GuiManager.h"

#define ACTION_RESIZE -1
#define ACTION_CANCEL 100

class GuiManager;

class Input
{
public:
    Input();

    ~Input();

    void handle_input(bool *run_flag, GuiManager *gui_mgr);

    SDL_Event m_event;
    bool m_unfocused;
};

#endif