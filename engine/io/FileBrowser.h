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
#define FILE_NAME_MAX_WIDTH 350

#include <string.h>
#include <vector>
#include <memory>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <algorithm>
#endif

#include "SDL.h"
#include "../screen/Screen.h"
#include "../core/render/Renderer.h"
#include "../screen/Layout.h"
#include "../screen/elements/Label.h"
#include "../screen/elements/Button.h"
#include "../util/Lang.h"
#include "../screen/elements/GuiElement.h"

class GuiElement;

class FileBrowser
{
public:
	FileBrowser();
	FileBrowser(int type, std::string start_folder, Screen* parent);

	~FileBrowser();
	
	void init(void);
	void refresh(void);
	void close(void);

	void get_files_in_directory(std::string directory);
	void go_up();
	void go_to(std::string dir);
	void scroll(int dir);

#ifdef _WIN32
	std::wstring utf8toUtf16(const std::string & str);
#endif

	void handle_event(SDL_Event* e);
	void draw(Renderer* r, Layout* l);

private:
	std::vector<std::unique_ptr<GuiElement>> m_screen_elements;
	std::vector<std::string> m_file_list;
	std::vector<bool> m_file_type;

	int m_type;
	std::string m_title;
	std::string m_current_path;
	std::string m_selected_file;

	Screen* m_parent;
	SDL_Rect m_dim;
	SDL_Rect m_title_bar;
	SDL_Rect m_scroll_bar;
	SDL_Rect m_list_dim;

	bool m_dragging;
	bool m_valid_dir;

	int m_offset_x, m_offset_y;
	int m_scroll_offset;
	int m_line_height;
	int m_mouse_over;
	int m_selected;
};

#endif