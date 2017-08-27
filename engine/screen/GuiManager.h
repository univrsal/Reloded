/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "Screen.h"
#include "menus/GameScreen.h"
#include "menus/SpSetupScreen.h"
#include "menus/LevelBrowser.h"
#include "../util/Textures.h"
#include "../core/Input.h"
#include "Layout.h"
#include "../core/Resources.h"

#define GUI_NONE -1
#define GUI_GAME 0
#define GUI_SP 1
#define GUI_LB 2

class Resources;

class Layout;

class Texture;

class Input;

class GuiManager
{
public:
    GuiManager();

    ~GuiManager();

    void init(Resources* r);

    void draw_gui(void);

    void queue_screen(uint8_t gui_id);

    Screen *get_active_screen();

    int8_t m_next_screen;
    Texture *m_bg;
    Screen *m_current_screen;
	Resources* m_resources;
	Layout* m_layout;
private:
	void set_screen(uint8_t gui_id);

};

#endif