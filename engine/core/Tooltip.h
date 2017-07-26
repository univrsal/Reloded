/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <vector>
#include <string.h>
#include "../screen/Screen.h"

#define TOOLTIP_LINE_SPACE 2
#define TOOLTIP_BORDER 5

class Screen;

class Tooltip
{
public:
    Tooltip(Screen *parent_screen);

    ~Tooltip();

    void draw(void);

    void close(void);

    void set_pos(int x, int y);

    void set_text(std::string *text);

private:
    Screen *m_parent_screen;
    SDL_Rect m_dimensions;
    bool m_is_visible;
    int m_line_height;
    std::vector<std::string *> m_formatted_text;
    SDL_Color *m_bg_color;

    const std::string m_delmiter = "\n";
};

#endif