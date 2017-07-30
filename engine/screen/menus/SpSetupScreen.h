/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef RELODED_SPSETUPSCREEN_H
#define RELODED_SPSETUPSCREEN_H

#include <vector>
#include <memory>
#include <algorithm> 
#include "../../core/render/Texture.h"
#include "../../util/Textures.h"
#include "../../util/Lang.h"
#include "../elements/Button.h"
#include "../../core/audio/Sfx.h"
#include "../../util/Sounds.h"
#include "../elements/Label.h"
#include "../../io/Puzzle.h"
#include "../FileBrowser.h"
#include "../../core/Resources.h"
#include "../Screen.h"
#include "../../core/Tooltip.h"

class Label;

class FileBrowser;

class Resources;

class Screen;

class GuiElement;

class SpSetupScreen : public Screen
{
public:
    SpSetupScreen();

    ~SpSetupScreen();

    void draw_background(void);

    void draw_foreground(void);

	void init(Resources* r);

    void set_active_tooltip(std::string *text, int x, int y);

	void handle_events(void);

    Sfx *get_sfx_for_element(int element_type);

    void action_performed(int action_id);

    void close(void);

	void load_puzzle(void);

	void select_puzzle(int id);

private:
    std::vector<std::unique_ptr<GuiElement>> m_screen_elements;

	int m_level_number;
	char m_selected_level_format[3];
	
	std::string m_selected_level_string;
	std::string m_selected_level_path;
	std::string m_level_folder;

    Texture *m_border;
    Texture *m_content;

	Label *m_level_label;
	Label *m_level_name_label;

	Sfx *m_rock;
	Sfx *m_soft_rock;
	Sfx *m_alarm;
	Sfx *m_portal;

	FileBrowser* m_file_browser;
	Puzzle* m_current_puzzle;

	bool m_in_file_browser;
};


#endif //RELODED_SPSETUPSCREEN_H
