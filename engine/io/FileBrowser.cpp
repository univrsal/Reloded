#include "FileBrowser.h"

FileBrowser::FileBrowser()
{
	m_type = FILETYPE_OPEN;
	m_current_path = std::string("./");
	m_parent = NULL;
	m_dim = {};
	m_title_bar = {};
	m_title = "Choose a file";
	m_dragging = false;
	m_valid_dir = false;
	m_offset_x = m_offset_y = 0;
	m_line_height = 0;
}

FileBrowser::FileBrowser(int type, std::string start_folder, Screen* parent)
{
	m_type = type;
	m_current_path = start_folder;
	m_parent = parent;
	m_dim = { 0, 0, 400, 300 };
	m_title_bar = { 2, 2, m_dim.w - 4, 22};
	m_dragging = false;
	m_valid_dir = false;
	m_offset_x = m_offset_y = 0;
	m_line_height = 0;
	m_selected = 0;

	switch (type)
	{
	case FILETYPE_SAVE:
		m_title = "Save file";
		break;
	default:
	case FILETYPE_OPEN:
		m_title = "Open file";
		break;
	}
}

void FileBrowser::init(void)
{
	m_screen_elements.emplace_back(new Label(30, 260, 35, LABEL_DEFAULT, LANG_FB_TITLE, m_parent));
	SDL_Rect* temp = m_parent->m_resources->layout()->get_window_size();

	m_dim.x = temp->w / 2 - m_dim.w / 2;
	m_dim.y = temp->h / 2 - m_dim.h / 2;
	m_title_bar.x = m_dim.x + 2;
	m_title_bar.y = m_dim.y + 2;

	std::string line = "test";
	m_line_height = m_parent->m_resources->renderer()->util_text_default_dim(&line).h + 2;
}

void FileBrowser::refresh(void)
{
	printf("CURRENT PATH %s\n", m_current_path.c_str());

	m_selected = 0;

	m_selected_file.clear();
	m_file_list.clear();
	m_file_type.clear();

	get_files_in_directory(m_current_path);

	m_list_dim = { m_dim.x + 4, m_dim.y + 45, m_dim.w - 8, m_dim.h - 70 };
	
	m_scroll_offset = 0;
	m_scroll_bar = { m_dim.x + m_dim.w - 17, m_list_dim.y + 3, 10, 0 };
	m_scroll_bar.h = (m_list_dim.h - 6) * (((float)FILE_LIST_SPACE) / m_file_list.size());
}

void FileBrowser::close(void)
{
	m_screen_elements.clear();
	m_file_type.clear();
	m_file_list.clear();
	m_parent = NULL;
}

void FileBrowser::get_files_in_directory(std::string directory)
{
#ifdef _WIN32

	HANDLE hFind;
	WIN32_FIND_DATA data;
	std::wstring path = utf8toUtf16(directory.c_str());
	path.append(L"/*.*");
	char def_char = ' ';
	hFind = FindFirstFile(path.c_str() , &data);
	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Error while reading directory %s! File Handle was invalid\n", path.c_str());
		// We still need the option to go back
		m_file_list.push_back(".");
		m_file_list.push_back("..");
		m_file_type.push_back(true);
		m_file_type.push_back(true);
		return;
	}
	else
	{
		do {
			std::wstring file_name(data.cFileName);
			std::string std_string(file_name.begin(), file_name.end());
			m_file_list.push_back(std_string);
			m_file_type.push_back((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		} while (FindNextFile(hFind, &data));

		FindClose(hFind);
	}
#else
	DIR *dir;
	struct dirent *dirent;

	dir = opendir(directory.c_str());

	if (dir != NULL) {
		while ((dirent = readdir(dir))) {
			m_file_list.push_back(std::string(dirent->d_name));
			m_file_type.push_back(dirent->d_type == DT_DIR);
		}
		// Linux doesn't return the file list ordered
		std::sort(m_file_list.begin(), m_file_list.end());
	} else {
		printf("Error DIR* for %s was null!\n", directory.c_str());
		//We'll still need these
		m_file_list.push_back(".");
		m_file_list.push_back("..");
		m_file_type.push_back(true);
		m_file_type.push_back(true);
	}

	closedir(dir);
#endif
}

void FileBrowser::go_up()
{
	auto pos = m_current_path.rfind('/');
	if (pos != std::string::npos)
	{
		m_current_path.erase(pos);
		refresh();
	}
}

void FileBrowser::go_to(std::string dir)
{
	m_current_path.append("/").append(dir);
	refresh();
}

void FileBrowser::scroll(int dir)
{
	if (m_file_list.size() <= FILE_LIST_SPACE)
		return;
	int new_offset;

	if (dir < 0)
	{
		new_offset = m_scroll_offset + 1;
		m_scroll_offset = SDL_min(m_file_list.size() - FILE_LIST_SPACE, new_offset);
	}
	else
	{
		new_offset = m_scroll_offset - 1;
		m_scroll_offset = SDL_max(0, new_offset);
	}
}

#ifdef _WIN32
std::wstring FileBrowser::utf8toUtf16(const std::string & str)
{
	if (str.empty())
		return std::wstring();

	size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0,
		str.data(), (int)str.size(), NULL, 0);
	if (charsNeeded == 0)
		throw std::runtime_error("Failed converting UTF-8 string to UTF-16");

	std::vector<wchar_t> buffer(charsNeeded);
	int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0,
		str.data(), (int)str.size(), &buffer[0], buffer.size());
	if (charsConverted == 0)
		throw std::runtime_error("Failed converting UTF-8 string to UTF-16");

	return std::wstring(&buffer[0], charsConverted);
}
#endif

void FileBrowser::handle_event(SDL_Event * e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if (m_parent->m_resources->util_is_in_rect(&m_title_bar, e->button.x, e->button.y))
			{
				m_offset_x = e->button.x - m_title_bar.x;
				m_offset_y = e->button.y - m_title_bar.y;
				m_dragging = true;
			}
			else
			{
				if (m_mouse_over >= 0)
				{
					if (m_mouse_over + m_scroll_offset < m_file_list.size())
					{
						if (m_selected == m_mouse_over + m_scroll_offset)
						{
							// Double click
							if (m_selected == 1) // One directory up is always second in the list
							{
								go_up();
							}
							else if (m_selected > 0) // first element is always "./"
							{
								if (m_file_type[m_selected]) // When true: selection is a directory
								{
									go_to(m_selected_file);
								}
							}
						}
						else
						{
							m_selected = m_mouse_over + m_scroll_offset;
							m_selected_file = m_file_list[m_selected];
						}
					}
				}
			}
		}
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			m_dragging = false;
		}
	}
	else if (e->type == SDL_MOUSEMOTION)
	{
		if (m_dragging)
		{
			m_dim.x = e->button.x - m_offset_x;
			m_title_bar.x = m_dim.x + 2;
			m_dim.y = e->button.y - m_offset_y;
			m_title_bar.y = m_dim.y + 2;

			m_list_dim.x = m_dim.x + 4;
			m_list_dim.y = m_dim.y + 45;

			m_scroll_bar.x = m_dim.x + m_dim.w - 17;
			m_scroll_bar.y = m_list_dim.y + 3;
		}

		if (m_parent->m_resources->util_is_in_rect(m_list_dim.x, m_list_dim.y, m_list_dim.w - 15, m_list_dim.h,
												   e->button.x, e->button.y))
		{
			int m_y = e->button.y - m_list_dim.y;
			m_mouse_over = SDL_min(m_y / m_line_height, m_file_list.size());
		}
		else
		{
			m_mouse_over = -1;
		}
	}
	else if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_UP)
		{
			m_selected = SDL_max(m_selected - 1, 0);
			if (m_selected < m_scroll_offset)
				scroll(1);
		}
		else if (e->key.keysym.sym == SDLK_DOWN)
		{
			m_selected = SDL_min(m_selected + 1, m_file_list.size() - 1);
			if (m_selected > m_scroll_offset + FILE_LIST_SPACE - 1)
				scroll(-1);
		}
		else if (e->key.keysym.sym == SDLK_PAGEUP)
		{
			scroll(1);
		}
		else if (e->key.keysym.sym)
		{
			scroll(-1);
		}
	}
	
	std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

	for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
		iterator->get()->handle_events(m_parent->m_resources->input_event());
	}
}

void FileBrowser::draw(Renderer * r, Layout * l)
{
	// Main border
	r->util_fill_rect_shadow(&m_dim, r->m_palette->gray());
	// Title frame
	r->util_fill_rect(&m_title_bar, r->m_palette->blue());
	r->util_text_default(&m_title, m_dim.x + 4, m_dim.y + 4);
	// File list border
	r->util_draw_rect(&m_list_dim, r->m_palette->dark_gray());

	{ // File list
		int line_width = 0;
		bool was_cut = false;
		int j = 0;
		std::string line = m_current_path;

		// Current path
		line_width = r->util_text_default_dim(&line).w; // Cutting filenames that are too long
		while (line_width > m_dim.w - 8) {
			line = line.substr(1, line.size());
			line_width = r->util_text_default_dim(&line).w;
			was_cut = true;
		}

		if (was_cut)
			line = "..." + line;

		r->util_text_default(&line, m_title_bar.x + 2, m_title_bar.y + m_title_bar.h + 2,
							 m_parent->m_resources->palette()->black());

		for (int i = m_scroll_offset; i < m_file_list.size() + m_scroll_offset; i++) {
			line = m_file_list[i];
			was_cut = false;

			if (i == m_selected)
				r->util_fill_rect(m_list_dim.x + 2, m_list_dim.y + 3 + (m_line_height * j), m_list_dim.w - 20, m_line_height);

			line_width = r->util_text_default_dim(&line).w; // Cutting filenames that are too long
			while (line_width > FILE_NAME_MAX_WIDTH) {
				line = line.substr(0, line.size() - 1);
				line_width = r->util_text_default_dim(&line).w;
				was_cut = true;
			}

			if (j == m_mouse_over)
				r->util_draw_rect(m_list_dim.x + 2, m_list_dim.y + 3 + m_line_height * j, m_list_dim.w - 20, m_line_height, m_parent->m_resources->palette()->dark_gray());
			
			if (m_file_type[i]) // Mark directories with '/'
				line.append("/");

			if (was_cut)
				line.append("...");

			r->util_text_default(&line, m_dim.x + 8, m_list_dim.y + 3 + (m_line_height * j), m_parent->m_resources->palette()->black());
			
			j++;
			if (j >= FILE_LIST_SPACE)
				break;
		}
	}

	{ // Scroll bar
		if (m_file_list.size() > FILE_LIST_SPACE)
		{
			m_scroll_bar.y = m_list_dim.y + 3 + (m_list_dim.h - 6 - m_scroll_bar.h) * (((float)m_scroll_offset / (m_file_list.size() - FILE_LIST_SPACE)));
			r->util_fill_rect(&m_scroll_bar, r->m_palette->dark_gray());
		}
	}
}

FileBrowser::~FileBrowser()
{
	close();
}
