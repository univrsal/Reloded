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

#include <string>
#include <vector>
#include <memory>

#include "SDL.h"
#include "Screen.h"
#include "../core/render/Renderer.h"
#include "Layout.h"
#include "elements/GuiElement.h"
#include "elements/Label.h"
#include "elements/Button.h"
#include "../util/Lang.h"

class FileBrowser
{
public:
	FileBrowser();
	FileBrowser(int type, std::string start_folder, Screen* parent);

	~FileBrowser();
	
	void init();
	void close(void);

	void handle_event(SDL_Event* e);
	void draw(Renderer* r, Layout* l);

	
private:
	std::vector<std::unique_ptr<GuiElement>> m_screen_elements;
	int m_type;
	std::string m_current_path;
	std::string m_selected_file;
	Screen* m_parent;
};

#endif