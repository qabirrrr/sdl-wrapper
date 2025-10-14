#include "../../include/render"
#include "../../include/globals"

namespace sdl 
{
    namespace render
	{
		void clear()
		{
			SDL_RenderClear(g_renderer);
		}

		void present()
		{
			SDL_RenderPresent(g_renderer);
		}

		void color(const color_t& color)
		{
			SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
		}
	}
}