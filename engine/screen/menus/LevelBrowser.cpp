#include "LevelBrowser.h"


LevelBrowser::LevelBrowser()
{
    m_border = NULL;
}


LevelBrowser::~LevelBrowser()
{
    delete m_border;

    m_border = NULL;
}

void LevelBrowser::init(Resources * r)
{
    m_resources = r;

    m_resources->layout()->set_content_dim(400, 350);
    m_border = new Texture(CONST_PATH_LB_BORDER, m_resources->sdl_renderer(), m_resources->scalef());

    m_screen_elements.emplace_back(
            new Button(0, BTN_MEDIUM_ACCEPT, 228, 280, CONST_PATH_BTN_RUN, LANG_LB_RUN, this));
    m_screen_elements.emplace_back(
            new Button(1, BTN_MEDIUM_CANCEL, 294, 280, CONST_PATH_BTN_CANCEL, LANG_LB_CANCEL, this));

    m_level_name = new Label(2, 25, 239, LABEL_GOLD, m_resources->get_current_level_name().c_str(), this);
    m_scrollbar = new Scrollbar(5, 362, 22, 197, m_resources->puzzle()->get_level_count() - 1, SCROLL_TYPE_INGAME,
                                this);

    m_screen_elements.emplace_back(new Panel(3, 25, 239, 350, 14, LANG_LB_LEVEL_NAME, this));
    m_screen_elements.emplace_back(new Panel(4, 22, 22, 340, 197, LANG_LB_PREVIEW, this));
    m_screen_elements.emplace_back(m_scrollbar);
    m_screen_elements.emplace_back(m_level_name);

    m_tooltip = new Tooltip(this);

    m_scrollbar->set_offset(m_resources->level_id());
}

void LevelBrowser::draw_foreground(void)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_foreground();
    }

    m_tooltip->draw();
}

void LevelBrowser::draw_background(void)
{
    m_border->draw(m_resources->sdl_renderer(), m_resources->origin());

    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->draw_background();
    }
}

void LevelBrowser::handle_events(void)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
        iterator->get()->handle_events(m_resources->input_event());
    }

    m_resources->set_level_id(m_scrollbar->get_offset());
    m_level_name->set_text(m_resources->get_current_level_name());
}

Sfx * LevelBrowser::get_sfx_for_element(uint8_t element_type)
{
    switch (element_type)
    {
        default:
        case BTN_MEDIUM_CANCEL:
            return NULL;
        case BTN_MEDIUM_ACCEPT:
            return NULL;
    }
}

void LevelBrowser::close(void)
{
    m_border->free();
    m_resources->layout()->reset_content_dim();
    m_screen_elements.clear();
}

void LevelBrowser::action_performed(int8_t action_id)
{
    std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

    switch (action_id)
    {
        case ACTION_RESIZE:
            for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++)
            {
                iterator->get()->resize();
            }
            break;
    }
}

void LevelBrowser::set_active_tooltip(std::string *text, uint16_t x, uint16_t y)
{
    m_tooltip->set_text(text);
    m_tooltip->set_pos(x, y);
}
