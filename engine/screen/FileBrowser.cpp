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
	m_screen_elements.emplace_back(new Label(0, 260, 35, LABEL_DEFAULT, LANG_FB_TITLE, m_parent));
	SDL_Rect* temp = m_parent->m_resources->layout()->get_window_size();

	m_dim.x = temp->w / 2 - m_dim.w / 2;
	m_dim.y = temp->h / 2 - m_dim.h / 2;
	m_title_bar.x = m_dim.x + 2;
	m_title_bar.y = m_dim.y + 2;

	std::string line = "test";
	m_line_height = m_parent->m_resources->renderer()->util_text_default_dim(&line).h + 2;
	get_files_in_directory(m_current_path);
}

void FileBrowser::close(void)
{
	m_screen_elements.clear();
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
		return;
	}
	else
	{
		do {
			std::wstring file_name(data.cFileName);
			std::string test(file_name.begin(), file_name.end());
			m_file_list.push_back(file_name);
			m_file_type.push_back((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		} while (FindNextFile(hFind, &data));

		FindClose(hFind);
	}
#else
	DIR *dir;
	class dirent *ent;
	class stat st;

	dir = opendir(directory);
	while ((ent = readdir(dir)) != NULL) {
		const string file_name = ent->d_name;
		const string full_file_name = directory + "/" + file_name;

		if (file_name[0] == '.')
			continue;

		if (stat(full_file_name.c_str(), &st) == -1)
			continue;

		const bool is_directory = (st.st_mode & S_IFDIR) != 0;

		if (is_directory)
			continue;

		out.push_back(full_file_name);
	}
	closedir(dir);
#endif
}

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

void FileBrowser::handle_event(SDL_Event * e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if (e->button.x >= m_title_bar.x && e->button.x <= m_title_bar.x + m_title_bar.w && e->button.y >= m_title_bar.y
				&& e->button.y <= m_title_bar.y + m_title_bar.h)
			{
				m_offset_x = e->button.x - m_title_bar.x;
				m_offset_y = e->button.y - m_title_bar.y;
				m_dragging = true;
			}
		}
	}
	else if (e->type == SDL_MOUSEBUTTONUP) {
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
		}
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
	r->util_draw_rect(m_dim.x + 4, m_dim.y + 28, m_dim.w - 8, m_dim.h - 70, r->m_palette->dark_gray());
	
	{ // File list
		
		std::vector<std::wstring>::iterator iterator;
		std::string t;
		int i = 0;

		for (iterator = m_file_list.begin(); iterator != m_file_list.end(); iterator++) {
			t = std::string(iterator->begin(), iterator->end());
			r->util_text_default(&t, m_dim.x + 8, m_dim.y + 32 + (m_line_height * i), m_parent->m_resources->palette()->black());
			i++;
		}
	}
}

FileBrowser::~FileBrowser()
{
	close();
}
