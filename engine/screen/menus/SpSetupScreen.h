/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef RELODED_SPSETUPSCREEN_H
#define RELODED_SPSETUPSCREEN_H


#include <vector>
#include <memory>
#include "../../core/Input.h"
#include "../Screen.h"
#include "../../core/Texture.h"
#include "../../util/Textures.h"
#include "../../util/Lang.h"
#include "../elements/Button.h"
#include "../../core/audio/Sfx.h"
#include "../../util/Sounds.h"

class SpSetupScreen : public Screen
{
public:
    SpSetupScreen();

    ~SpSetupScreen();

    void draw_background(void);

    void draw_foreground(void);

    void init(SDL_Event *sdl_event, Renderer *renderer, Layout *layout);

    void set_active_tooltip(std::string *text, int x, int y);

    Sfx *get_sfx_for_element(int element_type);

    void action_performed(int action_id);

    void close(void);

private:
    std::vector<std::unique_ptr<GuiElement>> m_screen_elements;

    Texture *m_border;
    Texture *m_content;
    
	Sfx *m_rock;
	Sfx *m_soft_rock;
};


#endif //RELODED_SPSETUPSCREEN_H
