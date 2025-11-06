#include "../../include/keys"
#include "../../include/globals"
#include <iostream>
#include <cstring>

namespace sdl 
{
    namespace keys
	{
		void copy_key(uint8_t* dst, const uint8_t* src) 
		{
			std::memcpy(dst, src, SDL_NUM_SCANCODES * sizeof(uint8_t));
		}

		void end_frame()
		{
			copy_key(g_previous_keystate, g_current_keystate); // previousState = currentState;  (essentially)
		}

		bool pressed(SDL_Scancode key)
		{
			return g_current_keystate[key] && !g_previous_keystate[key];
		}

		bool released(SDL_Scancode key)
		{
			return !g_current_keystate[key] && g_previous_keystate[key];
		}


		bool held(SDL_Scancode key)
		{
			return g_current_keystate[key];
		}
	}
}