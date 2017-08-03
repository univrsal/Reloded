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

	m_offset_x = m_offset_y = 0;
}

FileBrowser::FileBrowser(int type, std::string start_folder, Screen* parent)
{
	m_type = type;
	m_current_path = start_folder;
	m_parent = parent;
	m_dim = { 0, 0, 400, 300 };
	m_title_bar = { 2, 2, m_dim.w - 4, 22};
	m_dragging = false;

	m_offset_x = m_offset_y = 0;

    switch (m_type)
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
	SDL_Rect* temp = m_parent->m_resources->layout()->get_window_size();

	m_dim.x = temp->w / 2 - m_dim.w / 2;
	m_dim.y = temp->h / 2 - m_dim.h / 2;
	m_title_bar.x = m_dim.x + 2;
	m_title_bar.y = m_dim.y + 2;

    m_path_text = new Textbox(30, m_title_bar.x + 2, m_title_bar.y + m_title_bar.h + 2, 100, 20, std::string(""),
                              m_parent);
	m_list_box = new ListBox(31, m_dim.x + 4, m_path_text->get_dimensions()->y + m_path_text->get_dimensions()->h + 2, m_dim.w - 8, FILE_LIST_SPACE, m_parent);
    
	m_screen_elements.emplace_back(m_path_text);
	m_screen_elements.emplace_back(m_list_box);
}

void FileBrowser::refresh(void)
{
	printf("CURRENT PATH %s\n", m_current_path.c_str());

	m_selected_file.clear();
	m_file_list.clear();

	get_files_in_directory(m_current_path);
	m_list_box->set_list(m_file_list);
}

void FileBrowser::close(void)
{
	m_screen_elements.clear();
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
		return;
	}
	else
	{
		do {
			std::wstring file_name(data.cFileName);
			std::string std_string(file_name.begin(), file_name.end());
			m_file_list.push_back(std_string);
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
		}
		// Linux doesn't return the file list ordered
		std::sort(m_file_list.begin(), m_file_list.end());
	} else {
		printf("Error DIR* for %s was null!\n", directory.c_str());
		//We'll still need these
		m_file_list.push_back(".");
		m_file_list.push_back("..");
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

void FileBrowser::update_dir(void)
{
	std::string new_dir = m_list_box->get_selected();

	if (new_dir.compare("..") == 0)
	{
		go_up();
	}
	else
	{
		go_to(new_dir);
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

            // Move Elements
            m_path_text->set_pos(m_title_bar.x + 2, m_title_bar.y + m_title_bar.h + 2);
			m_list_box->set_pos(m_dim.x + 4, m_path_text->get_dimensions()->y + m_path_text->get_dimensions()->h + 2);
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

    { // Input elements
        std::vector<std::unique_ptr<GuiElement>>::iterator iterator;

        for (iterator = m_screen_elements.begin(); iterator != m_screen_elements.end(); iterator++) {
            iterator->get()->draw_background();
            iterator->get()->draw_foreground();
        }
    }
}

FileBrowser::~FileBrowser()
{
	close();
}

bool FileBrowser::is_dir(std::string file)
{
#ifdef _WIN32
	return false;
#else
    std::string temp_path = m_current_path + "/" + file;
    DIR *d = opendir(temp_path.c_str());
    bool result = d != NULL;
    if (d)
        closedir(d);
    return result;
#endif
}
