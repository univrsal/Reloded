//
// Created by universal on 14.07.17.
//

#include "SpSetupScreen.h"

SpSetupScreen::SpSetupScreen()
{
    m_current_event = NULL;
    m_renderer = NULL;
    m_layout = NULL;
    m_border = NULL;
    m_content = NULL;
    m_tooltip = NULL;
}

SpSetupScreen::~SpSetupScreen()
{
    close();
}

void SpSetupScreen::draw_background(void)
{
//    m_border->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin());
//    m_content->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin(), 22, 22);

    // Draw gui elements
//    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;
//    GuiElement* e = NULL;
//
//    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
//        e = iterator->get();
//
//        e->handle_event(m_current_event);
//        e->draw_background();
//    }

//    m_tooltip->draw_background();
}

void SpSetupScreen::draw_foreground(void)
{

//    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;
//
//    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
//        iterator->get()->draw_foreground();
//    }
}

void SpSetupScreen::init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout)
{
    m_current_event = NULL;
    m_renderer = NULL;
    m_layout = NULL;

    m_layout = layout;
    m_current_event = sdl_event;
    m_renderer = renderer;

//    m_border = new Texture(CONST_PATH_MENU_BORDER, renderer->m_sdl_renderer, m_layout->get_scale_factor());
//    m_content = new Texture(CONST_PATH_SP_CONTENT, renderer->m_sdl_renderer, m_layout->get_scale_factor());

    //m_screen_elements.emplace_back(new Button(0, BTN_BIG, 48, 285, CONST_PATH_BTN_SP, LANG_TIP_SP, this));
    //m_screen_elements.emplace_back(new Button(1, BTN_BIG, 170, 285, CONST_PATH_BTN_LOCAL_MP, LANG_TIP_LOCAL_MP, this));
    //m_screen_elements.emplace_back(new Button(2, BTN_BIG, 303, 285, CONST_PATH_BTN_NET_MP, LANG_TIP_NET_MP, this));
    //m_screen_elements.emplace_back(new Button(3, BTN_MEDIUM, 546, 286, CONST_PATH_BTN_MAP_EDITOR, LANG_TIP_MAP_EDITOR, this));
    //m_screen_elements.emplace_back(new Button(4, BTN_MEDIUM, 546, 331, CONST_PATH_BTN_SETTINGS, LANG_TIP_SETTINGS, this));

//    m_rock = new Sfx(SFX_EFFECT, SFX_PATH_ROCK);
//    m_soft_rock = new Sfx(SFX_EFFECT, SFX_PATH_ROCK_SOFT);

    //Singleplayer specific buttons

    m_tooltip = new Tooltip(this);
}

void SpSetupScreen::set_active_tooltip(std::string *text, int x, int y)
{
//    m_tooltip->set_text(text);
//    m_tooltip->set_pos(x, y);
}

void SpSetupScreen::action_performed(int action_id)
{
//    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;
    switch (action_id) {
        case ACTION_RESIZE:
//            for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
//                iterator->get()->resize();
//            }
            break;
        case ACTION_CANCEL:
            m_renderer->m_gui_mgr->set_screen(GUI_GAME);
            break;
    }
}

void SpSetupScreen::close(void)
{
    m_current_event = NULL;
    m_renderer = NULL;
//    m_screen_elements.clear();
//    m_screen_elements.~vector();
//    m_soft_rock->~Sfx();
//    m_rock->~Sfx();
//    m_tooltip->~Tooltip();
//    m_border->~Texture();
//    m_content->~Texture();
}

Sfx *SpSetupScreen::get_sfx_for_element(int element_type)
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
