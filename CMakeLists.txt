cmake_minimum_required(VERSION 3.7)
project(reloded)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp engine/screen/elements/Button.cpp engine/core/Engine.cpp engine/screen/menus/GameScreen.cpp engine/screen/elements/GuiElement.cpp
        engine/screen/GuiManager.cpp engine/core/Input.cpp engine/screen/elements/Label.cpp engine/screen/Layout.cpp engine/core/render/Renderer.cpp engine/screen/Screen.h
        engine/core/render/Texture.cpp engine/core/Tooltip.cpp engine/core/render/Palette.cpp engine/core/render/Palette.h engine/core/render/FontHelper.cpp engine/core/Timer.cpp
        engine/core/Timer.h engine/screen/menus/SpSetupScreen.cpp engine/screen/menus/SpSetupScreen.h engine/core/audio/Audio.cpp engine/core/audio/Audio.h engine/core/audio/Sfx.cpp
        engine/core/audio/Sfx.h engine/io/Puzzle.cpp engine/core/Resources.cpp engine/io/FileBrowser.cpp engine/screen/elements/Textbox.cpp
        engine/screen/menus/LevelBrowser.cpp engine/screen/elements/ListBox.cpp engine/screen/elements/Scrollbar.cpp engine/screen/elements/Panel.cpp engine/screen/elements/Panel.h)
add_executable(reloded ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDLTTF2 REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDLTTF2_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDLTTF2_LIBRARIES} ${SDL2MIXER_LIBRARIES})