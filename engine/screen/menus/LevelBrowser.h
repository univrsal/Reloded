#pragma once
#include "../Screen.h"
#include "../../util/Textures.h"
#include "../../core/render/Texture.h"
#include "../../core/Resources.h"

class Resources;

class LevelBrowser :
	public Screen
{
public:
	LevelBrowser();
	~LevelBrowser();

	void init(Resources* r);

	void draw_background(void);

	void draw_foreground(void);

	void handle_events(void);

	Sfx *get_sfx_for_element(uint8_t element_type);
private:
	Texture *m_border;
};

