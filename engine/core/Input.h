/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include "../screen/GuiManager.h"

#define ACTION_RESIZE -1
#define ACTION_CANCEL -2
#define ACTION_SCROLL_UP -3
#define ACTION_SCROLL_DOWN -4
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