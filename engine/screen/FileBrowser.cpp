#include "FileBrowser.h"

FileBrowser::FileBrowser()
{
	m_type = FILETYPE_OPEN;
	m_current_path = std::string("./");
	m_parent = NULL;
}

FileBrowser::FileBrowser(int type, std::string start_folder, Screen* parent)
{
	m_type = type;
	m_current_path = start_folder;
	m_parent = parent;
}

void FileBrowser::init(void)
{
	m_screen_elements.emplace_back(new Label(0, 260, 35, LABEL_WHITE_SHADOW, LANG_FB_TITLE, m_parent));
}

void FileBrowser::close(void)
{
	m_screen_elements.clear();
}

void FileBrowser::handle_event(SDL_Event * e)
{
	
}

void FileBrowser::draw(Renderer * r, Layout * l)
{
	SDL_Rect temp = *l->get_content_size();
	int scale = (*l->get_scale_factor());

	{ // Border frame
		temp.x += 20 * scale; temp.y += 20 * scale; temp.w -= 40 * scale; temp.h -= 40 * scale;
		r->util_fill_rect_shadow(&temp, r->m_palette->get_tooltip_body());

		temp.x += 5 * scale; temp.y += 5 * scale; temp.w -= 10 * scale; temp.h -= 10 * scale;
		r->util_fill_rect(&temp, r->m_palette->gray());
	}

	{ // File list border
		temp.x += 2 * scale; temp.y += 30 * scale; temp.w -= 4 * scale; temp.h -= 60 * scale;
		r->util_fill_rect(&temp, r->m_palette->black());
	}
	
	std::string line = "FILE.PZL";
	int line_height = r->util_text_default_dim(&line).h + 2;
	
	{ // File list
		for (int i = 0; i < 5; i++)
		{
			r->util_text_default_scaled(&line, temp.x + 4, temp.y + (line_height * i));
		}
	}

	std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

	for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
		iterator->get()->draw_background();
		iterator->get()->draw_foreground();
	}
}

FileBrowser::~FileBrowser()
{
	close();
}
