/**
* Created by universallp on 14.07.2017.
* This file is part of reloded which is licenced
* under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
* github.com/univrsal/reloded
*/

#include "SpSetupScreen.h"

SpSetupScreen::SpSetupScreen()
{
    m_current_event = NULL;
    m_renderer = NULL;
    m_layout = NULL;
    m_border = NULL;
    m_content = NULL;
    m_tooltip = NULL;
	m_rock = NULL;
	m_soft_rock = NULL;
    m_portal = NULL;
    m_alarm = NULL;
    m_level_label = NULL;
    m_input = NULL;
	m_current_puzzle = NULL;
	m_level_name_label = NULL;
    m_level_number = 1;
}

SpSetupScreen::~SpSetupScreen()
{
    close();
    delete m_tooltip;
    delete m_content;
    delete m_border;
	delete m_rock;
	delete m_soft_rock;
    delete m_alarm;
    delete m_portal;
	delete m_current_puzzle;

	m_current_puzzle = NULL;
    m_input = NULL;
    m_level_label = NULL;
	m_level_name_label = NULL;
	m_portal = NULL;
    m_alarm = NULL;
    m_content = NULL;
    m_renderer = NULL;
    m_layout = NULL;
    m_current_event = NULL;
	m_rock = NULL;
	m_soft_rock = NULL;
}

void SpSetupScreen::draw_background(void)
{
    m_border->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin());
    m_content->draw(m_renderer->m_sdl_renderer, m_layout->get_content_origin(), 22, 22);

    // Draw gui elements
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_background();
    }
}

void SpSetupScreen::draw_foreground(void)
{
    m_tooltip->draw();
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_foreground();
    }
}

void SpSetupScreen::init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout, Input *input, Audio *audio)
{
	m_audio = audio;
    m_layout = layout;
    m_current_event = sdl_event;
    m_renderer = renderer;
    m_input = input;

    sprintf(m_selected_level_format, "%03d", m_level_number);
    m_selected_level_string = std::string(m_selected_level_format);

    m_border = new Texture(CONST_PATH_MENU_BORDER, renderer->m_sdl_renderer, m_layout->get_scale_factor());
    m_content = new Texture(CONST_PATH_SP_CONTENT, renderer->m_sdl_renderer, m_layout->get_scale_factor());

    // Bottom navigation
    m_screen_elements.emplace_back(new Button(0, BTN_BIG, 48, 285, CONST_PATH_BTN_SP, LANG_TIP_SP, this));
    m_screen_elements.emplace_back(new Button(1, BTN_BIG, 170, 285, CONST_PATH_BTN_LOCAL_MP, LANG_TIP_LOCAL_MP, this));
    m_screen_elements.emplace_back(new Button(2, BTN_BIG, 303, 285, CONST_PATH_BTN_NET_MP, LANG_TIP_NET_MP, this));
    m_screen_elements.emplace_back(
            new Button(3, BTN_MEDIUM, 546, 286, CONST_PATH_BTN_MAP_EDITOR, LANG_TIP_MAP_EDITOR, this));
    m_screen_elements.emplace_back(
            new Button(4, BTN_MEDIUM, 546, 331, CONST_PATH_BTN_SETTINGS, LANG_TIP_SETTINGS, this));

    // Screen specific buttons
    m_screen_elements.emplace_back(new Button(5, BTN_SMALL, 46, 44, CONST_PATH_BTN_LOAD, LANG_TIP_PZL_GROUP, this));
    m_screen_elements.emplace_back(
            new Button(6, BTN_SMALL, 91, 44, CONST_PATH_BTN_RESET, LANG_TIP_RESET_PZL_GROUP, this));
    m_screen_elements.emplace_back(new Button(6, BTN_SMALL, 500, 44, CONST_PATH_BTN_BROWSE, LANG_TIP_BROWSE_PZL, this));
    m_screen_elements.emplace_back(new Button(7, BTN_MICRO, 534, 45, CONST_PATH_BTN_UP, LANG_TIP_PZL_UP, this));
    m_screen_elements.emplace_back(new Button(8, BTN_MICRO, 534, 61, CONST_PATH_BTN_DOWN, LANG_TIP_PZL_DOWN, this));
    m_screen_elements.emplace_back(new Button(9, BTN_SMALL, 562, 44, CONST_PATH_BTN_RESET, LANG_TIP_PZL_RESET, this));

    m_screen_elements.emplace_back(
            new Button(10, BTN_MEDIUM_CANCEL, 479, 199, CONST_PATH_BTN_CANCEL, LANG_TIP_SP_CANCEL, this));
    m_screen_elements.emplace_back(
            new Button(11, BTN_MEDIUM_ACCEPT, 537, 199, CONST_PATH_BTN_RUN, LANG_TIP_SP_GO, this));

	// Current Puzzle Pack
	m_current_puzzle = new Puzzle();
	m_selected_level_path = "./res/lvl/mmr.PZL";
	load_puzzle();

    // Labels
    m_screen_elements.emplace_back(new Label(12, 241, 53, LABEL_TITLE, LANG_TITLE_SP, this));
    m_screen_elements.emplace_back(new Label(13, 53, 91, LABEL_GOLD, LANG_GROUP_SP, this));

	m_level_label = new Label(14, 365, 92, LABEL_GOLD, m_selected_level_string.c_str(), this);
	
	std::string* name = m_current_puzzle->get_level_name(m_level_number - 1);
	transform(name->begin(), name->end(), name->begin(), ::toupper);
	m_level_name_label = new Label(15, 407, 92, LABEL_GOLD, name->c_str(), this);
	
	m_screen_elements.emplace_back(m_level_label);
	m_screen_elements.emplace_back(m_level_name_label);

    m_rock = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_ROCK);
    m_soft_rock = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_ROCK_SOFT);
    m_alarm = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_CANCEL);
    m_portal = new Sfx(SFX_EFFECT, m_audio, SFX_PATH_ACCEPT);

    m_tooltip = new Tooltip(this);


}

void SpSetupScreen::set_active_tooltip(std::string *text, int x, int y)
{
    m_tooltip->set_text(text);
    m_tooltip->set_pos(x, y);
}

void SpSetupScreen::action_performed(int action_id)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    switch (action_id) {
        case ACTION_RESIZE:
            for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
                iterator->get()->resize();
            }
            break;
        case 10:
        case ACTION_CANCEL:
            m_renderer->m_gui_mgr->queue_screen(GUI_GAME);
            break;
        case 7:
        case ACTION_SCROLL_UP:
            if (m_level_number < m_current_puzzle->get_level_count())
                m_level_number++;
			select_puzzle(m_level_number);
            break;
        case 8:
        case ACTION_SCROLL_DOWN:
            if (m_level_number > 1)
                m_level_number--;
			select_puzzle(m_level_number);
            break;
        case 9:
            m_level_number = 1;
			select_puzzle(m_level_number);
            break;
    }
}

void SpSetupScreen::close(void)
{
    m_soft_rock->close();
    m_rock->close();
    m_tooltip->close();
    m_content->free();
    m_border->free();
	m_alarm->close();
	m_portal->close();
	m_current_puzzle->close();
    m_screen_elements.clear();
}

void SpSetupScreen::load_puzzle(void)
{
	m_current_puzzle->read_from_file(m_selected_level_path);
}

void SpSetupScreen::select_puzzle(int id)
{
	std::string name = *m_current_puzzle->get_level_name(id - 1);
	transform(name.begin(), name.end(), name.begin(), ::toupper);
	SDL_Rect dim = m_renderer->util_text_default_dim(&name, FONT_LODE);
	
	while (dim.w > 169) {
		name = name.substr(0, name.size() - 1);
		dim = m_renderer->util_text_default_dim(&name, FONT_LODE);
	}
	printf("WIDHT: %i\n", dim.w);

	m_level_name_label->set_text(name);

	sprintf(m_selected_level_format, "%03d", id);
	m_selected_level_string = std::string(m_selected_level_format);
	m_level_label->set_text(m_selected_level_string);
}

Sfx *SpSetupScreen::get_sfx_for_element(int element_type)
{
    switch (element_type) {
        case BTN_BIG:
            return m_rock;
        case BTN_MEDIUM_CANCEL:
            return m_alarm;
        case BTN_MEDIUM_ACCEPT:
            return m_portal;
        case BTN_MEDIUM:
        case BTN_SMALL:
        case BTN_MICRO:
            return m_soft_rock;
        default:
            return NULL;
    }
}

void SpSetupScreen::handle_events(void)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->handle_events(m_current_event);
    }
}
