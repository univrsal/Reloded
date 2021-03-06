/**
* Created by universallp on 29.07.2017.
* This file is part of reloded which is licenced
* under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
* github.com/univrsal/reloded
*/

#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#define FILETYPE_OPEN 0
#define FILETYPE_SAVE 1

#define FILE_LIST_SPACE 11

#include <string.h>
#include <vector>
#include <memory>
#include <stdio.h>
#include <algorithm>
#include "../screen/elements/GuiElement.h"
#include "../screen/elements/Button.h"
#include "../screen/elements/ListBox.h"
#include "../screen/elements/Textbox.h"

#ifdef _WIN32
#include <Windows.h>
#include <sys/stat.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#endif

#include "SDL.h"
#include "../screen/Screen.h"
#include "../core/render/Renderer.h"
#include "../screen/Layout.h"
#include "../screen/elements/Label.h"
#include "../screen/elements/Button.h"
#include "../screen/elements/Textbox.h"
#include "../screen/elements/ListBox.h"
#include "../util/Lang.h"
#include "../screen/elements/GuiElement.h"

class GuiElement;

class Textbox;

class ListBox;

class Button;

class FileBrowser
{
public:
	FileBrowser();

	FileBrowser(uint8_t type, std::string start_folder, std::string filter, Screen *parent);

	~FileBrowser();

	void init(void);

	void refresh(void);

	void close(void);

    bool is_dir(std::string file);

	void load_directory(std::string directory);

	void go_up();

	void go_to(std::string dir);

	void update_dir(void);

	bool matches_filter(std::string file);

#ifdef _WIN32
	std::wstring utf8toUtf16(const std::string & str);
#endif

	void handle_event(SDL_Event *e);

	void draw(Renderer *r, Layout *l);

	std::string get_file(void);

	std::string get_path(void);

private:
	std::vector<std::unique_ptr<GuiElement>> m_screen_elements;
	std::vector<std::string> *m_file_list;

	std::string m_title;
	std::string m_current_path;
	std::string m_selected_file;

	std::string m_filter;

    Textbox *m_path_text;
	ListBox *m_list_box;
	Button *m_accept;
	Button *m_cancel;

	Screen *m_parent;
	SDL_Rect m_dim;
	SDL_Rect m_title_bar;

	bool m_dragging;

    uint8_t m_type;
	uint16_t m_offset_x, m_offset_y;
};

#endif