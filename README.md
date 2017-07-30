# Reloded
Remake of Lode Runner: The Mad Monks' Revenge in SDL2

Selfmade remake of Lode Runner running on SDL2 and addon libraries

Disclaimer:
"Lode Runner" is a trademark of [Tozai](http://www.tozaigames.com/).
"Loder Runner Online: The Mad Monk's Revenge" developed by Presage is owned by [Activision/Sierra](http://sierra.com)
This project is not associated with either of the above companies.

#### Building:
You can either open the project in CLion with the cmakeslist.txt or directly build it using cmake.

Required libraries:
 * [SDL2](https://www.libsdl.org/)
 * [SDL_image](https://www.libsdl.org/projects/SDL_image/)
 * [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
 * [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)
 * [SDL_net](https://www.libsdl.org/projects/SDL_net/) (currently not required)

On linux just install the libraries over your package manager
For Arch:
`sudo pacman -S lib32-sdl2 lib32-sdl2_image lib32-sdl2_mixer lib32-sdl2_net`

With Windows it's a little harder, you can either setup VisualStudio with the libraries or use CLion with cygwin or Codeblocks.
For Codeblocks or VisualStudio you can follow [lazyfoo's tutorial](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).

Windows & Linux binaries will be available when it's in a playable state.
