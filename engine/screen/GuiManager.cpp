#include "GuiManager.h"

GuiManager::GuiManager()
{
    m_current_screen = NULL;
    m_resources = NULL;
    m_bg = NULL;
    m_next_screen = GUI_NONE;
}


GuiManager::~GuiManager()
{
    if (m_current_screen != NULL)
        m_current_screen->close();
    if (m_layout != NULL)
        m_layout->~Layout();

    m_layout = NULL;
    m_current_screen = NULL;
}

void GuiManager::init(Resources* r)
{
    m_resources = r;
    m_layout = new Layout(m_resources->window());
    m_resources->set_layout(m_layout);
    m_bg = new Texture(CONST_PATH_BG, m_resources->sdl_renderer());
}

void GuiManager::draw_gui(void)
{
    m_bg->draw_tiling(m_resources->sdl_renderer(), m_layout->get_window_size(), 1);

    if (m_current_screen) {
        m_current_screen->draw_background();
        m_current_screen->draw_foreground();
    }

    if (m_next_screen >= 0 && m_resources->audio()->get_is_sound_finished()) {
        set_screen(m_next_screen);
        m_next_screen = GUI_NONE;
    }
}

Screen *GuiManager::get_active_screen()
{
    return m_current_screen;
}

void GuiManager::set_screen(uint8_t gui_id)
{
    if (m_current_screen != NULL) {
        m_current_screen->close();
        m_current_screen = NULL;
    }

    switch (gui_id) {
        case GUI_GAME:
            m_current_screen = new GameScreen();
            break;
        case GUI_SP:
            m_current_screen = new SpSetupScreen();
            break;
        case GUI_LB:
            m_current_screen = new LevelBrowser();

            break;
    }

    m_current_screen->init(m_resources);
    m_current_screen->action_performed(ACTION_RESIZE);
}

void GuiManager::queue_screen(uint8_t gui_id)
{
    m_next_screen = gui_id;
}
