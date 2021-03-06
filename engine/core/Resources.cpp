#include "Resources.h"

Resources::Resources()
{
    m_renderer = NULL;
    m_audio = NULL;
    m_input = NULL;
    m_layout = NULL;
    m_engine = NULL;
    m_puzzle = NULL;
    m_puzzle = NULL;
}

Resources::~Resources()
{
    m_engine = NULL;
    m_audio = NULL;
    m_input = NULL;
    m_renderer = NULL;
    m_layout = NULL;

    if (m_puzzle != NULL)
    {
        m_puzzle->close();
        delete m_puzzle;
    }
    m_puzzle = NULL;
}

void Resources::init(Renderer * r, Audio * a, Input * i, Layout * l, Engine* e)
{
    m_renderer = r;
    m_audio = a;
    m_input = i;
    m_layout = l;
    m_engine = e;
}

Renderer * Resources::renderer(void)
{
    return m_renderer;
}

// Top left corner of screen with offset after scaling
SDL_Point * Resources::origin(void)
{
    return m_layout->get_content_origin();
}

SDL_Renderer * Resources::sdl_renderer(void)
{
    return m_renderer->m_sdl_renderer;
}

SDL_Window * Resources::window(void)
{
    return m_renderer->m_sdl_window;
}

Audio * Resources::audio(void)
{
    return m_audio;
}

Input * Resources::input(void)
{
    return m_input;
}

Layout * Resources::layout(void)
{
    return m_layout;
}

SDL_Event * Resources::input_event(void)
{
    return &m_input->m_event;
}

uint8_t * Resources::scalef(void)
{
    return m_layout->get_scale_factor();
}

Screen * Resources::active_screen(void)
{
    return m_renderer->m_gui_mgr->get_active_screen();
}

GuiManager * Resources::gui_mgr(void)
{
    return m_renderer->m_gui_mgr;
}

Palette * Resources::palette(void)
{
    return m_renderer->m_palette;
}

Puzzle * Resources::puzzle(void)
{
    return m_puzzle;
}

void Resources::set_puzzle(Puzzle * p)
{
    m_puzzle = p;
}

bool Resources::util_is_in_rect(const SDL_Rect *r, SDL_Point *p)
{
    return p->x >= r->x && p->x <= r->x + r->w
           && p->y >= r->y && p->y <= r->y + r->h;
}

bool Resources::util_is_in_rect(const SDL_Rect *r, int x, int y)
{
    return x >= r->x && x <= r->x + r->w
           && y >= r->y && y <= r->y + r->h;
}

bool Resources::util_is_in_rect(int x, int y, int w, int h, int x2, int y2)
{
    return x2 >= x && x2 <= x + w
           && y2 >= y && y2 <= y + h;
}

uint16_t Resources::level_id(void)
{
    return m_selected_level;
}

void Resources::set_level_id(int i)
{
    m_selected_level = (uint16_t) i;
}

std::string Resources::util_run_dir(void)
{
    std::string path = std::string(SDL_GetBasePath());
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
}

std::string Resources::util_res_dir(const char* sub_dir)
{
    return util_run_dir().append("res/").append(sub_dir);
}

void Resources::util_cut_string(std::string& s, int max_width, bool front)
{
    int w = m_renderer->util_text_default_dim(&s).w;
    bool was_cut = false;
    while (w > max_width)
    {
        if (front)
            s = s.substr(0, s.size() - 1);
        else
            s = s.substr(1, s.size());
        w = m_renderer->util_text_default_dim(&s).w;
        was_cut = true;
    }

    if (was_cut)
    {
        if (front)
            s.append("...");
        else
            s = "..." + s;
    }
}

void Resources::set_layout(Layout * l)
{
    m_layout = l;
}

std::string Resources::get_current_level_name(void)
{
    std::string name = *m_puzzle->get_level_name(m_selected_level);
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    return name;
}

SDL_Rect Resources::util_resize_rect(SDL_Rect r, int8_t v)
{
    r.x -= v;
    r.y -= v;
    r.w += v;
    r.h += v;
    return r;
}

SDL_Rect Resources::util_scale_rect(const SDL_Rect *r, int8_t v)
{
    return SDL_Rect {r->x * v, r->y * v, r->w * v, r->h * v};
}
