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
	m_border = new Texture(CONST_PATH_LB_BORDER, m_resources->sdl_renderer(), m_resources->scalef());
}

void LevelBrowser::draw_foreground(void)
{

}

void LevelBrowser::draw_background(void)
{
	m_border->draw(m_resources->sdl_renderer(), m_resources->origin());
}

void LevelBrowser::handle_events(void)
{

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