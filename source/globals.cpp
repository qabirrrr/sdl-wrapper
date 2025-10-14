#include "../../include/globals"

namespace sdl 
{
    SDL_Renderer* g_renderer;
	bool g_textures_loaded = true;
	bool g_running = true;

	bool g_left_clicked;
	bool g_right_clicked;
	SDL_Point g_mousepos;

	SDL_Window* g_window;
	int g_width;
	int g_height;
	Mix_Music* g_current_music;
	const uint8_t* g_current_keystate;
	uint8_t g_previous_keystate[SDL_NUM_SCANCODES] = {0};
	std::string g_character = "";
	bool g_char_typed = false;
}