#include "../../include/mouse"
#include "../../include/globals"

namespace sdl
{
    namespace mouse
	{
		bool hovered(const SDL_Rect& rect)
		{
			return SDL_PointInRect(&g_mousepos, &rect);
		}

		bool clicked_left(const SDL_Rect& rect)
		{
			return SDL_PointInRect(&g_mousepos, &rect) && g_left_clicked;
		}

		bool clicked_right(const SDL_Rect& rect)
		{
			return SDL_PointInRect(&g_mousepos, &rect) && g_right_clicked;
		}

		bool hovered(const rect_t& rect)
		{
			SDL_Rect r = rect.c_rec();
			return SDL_PointInRect(&g_mousepos, &r);
		}

		bool clicked_left(const rect_t& rect)
		{
			SDL_Rect r = rect.c_rec();
			return SDL_PointInRect(&g_mousepos, &r) && g_left_clicked;
		}

		bool clicked_right(const rect_t& rect)
		{
			SDL_Rect r = rect.c_rec();
			return SDL_PointInRect(&g_mousepos, &r) && g_right_clicked;
		}
	}
}