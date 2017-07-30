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

#include <string.h>
#include <vector>
#include <memory>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dirent.h>
#endif

#include "SDL.h"
#include "Screen.h"
#include "../core/render/Renderer.h"
#include "Layout.h"
#include "elements/Label.h"
#include "elements/Button.h"
#include "../util/Lang.h"
#include "elements/GuiElement.h"

class GuiElement;

class FileBrowser
{
public:
	FileBrowser();
	FileBrowser(int type, std::string start_folder, Screen* parent);

	~FileBrowser();
	
	void init();
	void close(void);

	void get_files_in_directory(std::string directory);

	std::wstring utf8toUtf16(const std::string & str);

	void handle_event(SDL_Event* e);
	void draw(Renderer* r, Layout* l);

private:
	std::vector<std::unique_ptr<GuiElement>> m_screen_elements;
	std::vector<std::wstring> m_file_list;
	std::vector<bool> m_file_type;

	int m_type;
	std::string m_title;
	std::string m_current_path;
	std::string m_selected_file;

	Screen* m_parent;
	SDL_Rect m_dim;
	SDL_Rect m_title_bar;
	bool m_dragging;
	bool m_valid_dir;
	int m_offset_x, m_offset_y;
	int m_line_height;
};

#endif