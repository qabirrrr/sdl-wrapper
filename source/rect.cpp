#include "../../include/rect"
#include "../../include/globals"
#include "../../include/mouse"
#include "../../include/sdl++"

namespace sdl 
{
    rect_t::rect_t(int x, int y, int w, int h, color_t color)
	{
		edit_properties(x, y, w, h);
		edit_color(color);
	}

	bool rect_t::operator==(const rect_t& other) const
	{
		return
		x == other.x &&
		y == other.y &&
		w == other.w &&
		h == other.h;
	}

	void rect_t::edit_color(const color_t& color)
	{
		m_color.r = color.r;
		m_color.g = color.g;
		m_color.b = color.b;
	}

	void rect_t::edit_properties(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}


	void rect_t::render_outline(uint8_t alpha)
	{
		SDL_Rect rect = { x, y, w, h };

		SDL_SetRenderDrawColor(g_renderer, m_color.r, m_color.g, m_color.b, alpha);
		SDL_RenderDrawRect(g_renderer, &rect);
	}

	void rect_t::render_fill(uint8_t alpha)
	{
		SDL_Rect rect = { x, y, w, h };

		SDL_SetRenderDrawColor(g_renderer, m_color.r, m_color.g, m_color.b, alpha);
		SDL_RenderFillRect(g_renderer, &rect);
	}

	bool rect_t::mouse_hovered()
	{
		SDL_Rect rect = { x,y,w,h };
		return mouse::hovered(rect);
	}

	bool rect_t::left_clicked()
	{
		SDL_Rect rect = { x,y,w,h };
		return mouse::clicked_left(rect);
	}

	bool rect_t::right_clicked()
	{
		SDL_Rect rect = { x,y,w,h };
		return mouse::clicked_right(rect);
	}


	bool rect_t::collided_width(const rect_t& rect) const
	{
		SDL_Rect rectA = { x, y, w, h };
		SDL_Rect rectB = rect.c_rec();
		return check_collisions(rectA, rectB);
	}

	bool rect_t::collided_with(const SDL_Rect& rect) const
	{
		SDL_Rect rectA = { x, y, w, h };
		return check_collisions(rectA, rect);
	}

	SDL_Rect rect_t::c_rec() const
	{
		return SDL_Rect{x, y, w, h};
	}
}