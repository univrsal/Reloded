#pragma once
#include "../Screen.h"
#include "../../util/Textures.h"
#include "../../core/render/Texture.h"
#include "../../core/Resources.h"
#include "../elements/Label.h"
#include "../elements/Button.h"
#include "../elements/Panel.h"

class Resources;

class Label;

class LevelBrowser :
		public Screen
{
public:
	LevelBrowser();

	~LevelBrowser();

	void init(Resources *r);

	void draw_background(void);

	void draw_foreground(void);

	void handle_events(void);

	void action_performed(int8_t action_id);

	void set_active_tooltip(std::string *text, uint16_t x, uint16_t y);

	void close(void);

	Sfx *get_sfx_for_element(uint8_t element_type);
private:
	std::vector<std::unique_ptr<GuiElement>> m_screen_elements;

    Label *m_level_name;
	Texture *m_border;
};

