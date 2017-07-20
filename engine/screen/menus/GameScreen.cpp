/**
* Created by universallp on 14.07.2017.
* This file is part of reloded which is licenced
* under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
* github.com/univrsal/reloded
*/

#include "GameScreen.h"

GameScreen::GameScreen()
{
	m_current_event = NULL;
	m_renderer = NULL;
	m_layout = NULL;
	m_border = NULL;
	m_logo = NULL;
	m_tooltip = NULL;
	m_rock = NULL;
	m_soft_rock = NULL;
    m_input = NULL;
}

GameScreen::~GameScreen()
{
    close();
    delete m_tooltip;
    delete m_logo;
    delete m_border;
	delete m_rock;
	delete m_soft_rock;

    m_input = NULL;
	m_tooltip = NULL;
	m_logo = NULL;
	m_border = NULL;
	m_soft_rock = NULL;
	m_rock = NULL;
    m_renderer = NULL;
    m_layout = NULL;
    m_current_event = NULL;
}

void GameScreen::draw_background(void)
{
    m_border->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin());
    m_logo->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin(), 22, 22);

    // Draw gui elements
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_background();
    }

    m_tooltip->draw();
}

void GameScreen::draw_foreground(void)
{
    // Draw top level things like tooltips
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_foreground();
    }
}

void GameScreen::init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout, Input *input, Audio *audio)
{
    m_input = input;
	m_audio = audio;
    m_layout = layout;
    m_current_event = sdl_event;
    m_renderer = renderer;

    m_logo = new Texture(CONST_PATH_LOGO, renderer->m_sdl_renderer, m_layout->get_scale_factor());
    m_border = new Texture(CONST_PATH_MENU_BORDER, renderer->m_sdl_renderer, m_layout->get_scale_factor());

    m_screen_elements.emplace_back(new Button(0, BTN_BIG, 48, 285, CONST_PATH_BTN_SP, LANG_TIP_SP, this));
    m_screen_elements.emplace_back(new Button(1, BTN_BIG, 170, 285, CONST_PATH_BTN_LOCAL_MP, LANG_TIP_LOCAL_MP, this));
    m_screen_elements.emplace_back(new Button(2, BTN_BIG, 303, 285, CONST_PATH_BTN_NET_MP, LANG_TIP_NET_MP, this));
    m_screen_elements.emplace_back(
            new Button(3, BTN_MEDIUM, 546, 286, CONST_PATH_BTN_MAP_EDITOR, LANG_TIP_MAP_EDITOR, this));
    m_screen_elements.emplace_back(
            new Button(4, BTN_MEDIUM, 546, 331, CONST_PATH_BTN_SETTINGS, LANG_TIP_SETTINGS, this));

    m_rock = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_ROCK);
    m_soft_rock = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_ROCK_SOFT);

    m_tooltip = new Tooltip(this);
}

void GameScreen::set_active_tooltip(std::string *text, int x, int y)
{
    m_tooltip->set_text(text);
    m_tooltip->set_pos(x, y);
}

void GameScreen::action_performed(int action_id)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;
    switch (action_id) {
        case ACTION_RESIZE:

            for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
                iterator->get()->resize();
            }
            break;
        case 0: // Singleplayer
            m_renderer->m_gui_mgr->queue_screen(GUI_SP);
            break;
        case 1: // Local multiplayer

            break;
        case 2: // Netplay

            break;
        case 3: // Map editor

            break;
        case 4: // Settings

            break;
        default:
            break;
    }
}

void GameScreen::close(void)
{
    m_soft_rock->close();
    m_rock->close();
    m_tooltip->close();
    m_logo->free();
    m_border->free();
    m_screen_elements.clear();
}

Sfx *GameScreen::get_sfx_for_element(int element_type)
{
    switch (element_type) {
        case BTN_BIG:
            return m_rock;
        case BTN_MEDIUM:
            return m_soft_rock;
        default:
            return NULL;
    }
}

void GameScreen::handle_events(void)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->handle_events(m_current_event);
    }
}
