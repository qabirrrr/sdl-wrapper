#include "../../include/text"
#include "../../include/mouse"
#include "../../include/globals"
#include "../../include/sdl++"

namespace sdl 
{
    text_t::text_t(const std::string& message, const color_t& color, font_t& font, uint8_t alpha, SDL_Point pos)
	{
		create(message, color, font, alpha, pos);
	}

	text_t::text_t(text_t&& old) noexcept
	{
		m_message = std::move(old.m_message);
		m_font = old.m_font;
		m_texture = std::move(old.m_texture);
		m_dst = old.m_dst;
		m_color = old.m_color;
		m_alpha = old.m_alpha;
	}

	text_t& text_t::operator=(text_t&& old) noexcept 
	{
		if (this != &old)
		{
			m_message = std::move(old.m_message);
			m_texture = std::move(old.m_texture);
			m_dst = old.m_dst;
			m_font = old.m_font;
			m_color = old.m_color;
			m_alpha = old.m_alpha;
			old.m_font= nullptr;
		}
		return *this;
	}

	void text_t::create(const std::string& message, const color_t& color, font_t& font, uint8_t alpha, SDL_Point pos) // https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
	{
		m_message = message;
		m_font = &font;
		m_color = color;
		m_alpha = alpha;

		int text_width;
		int text_height;
		SDL_Surface* surface;

		SDL_Texture*& tex = m_texture.get_raw();
		tex = nullptr;

		if (m_message.length() == 0)
		{
			return;
		}

		surface = TTF_RenderText_Blended(m_font->get_raw(), message.c_str(), color);
		tex = SDL_CreateTextureFromSurface(g_renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		SDL_FreeSurface(surface);

		m_dst.x = pos.x;
		m_dst.y = pos.y;
		m_dst.w = text_width;
		m_dst.h = text_height;
	}

	void text_t::edit_message(const std::string& message)
	{
		m_message = message;

		SDL_Texture*& tex = m_texture.get_raw();
		if (tex != nullptr)
		{
			SDL_DestroyTexture(tex);
			tex = nullptr;
		}

		if (m_message.length() == 0)
		{
			return;
		}

		int text_width;
		int text_height;
		SDL_Surface* surface;

		surface = TTF_RenderText_Blended(m_font->get_raw(), m_message.c_str(), m_color);
		tex = SDL_CreateTextureFromSurface(g_renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		SDL_FreeSurface(surface);

		SDL_SetTextureAlphaMod(tex, m_alpha);

		m_dst.w = text_width;
		m_dst.h = text_height;
	}

	void text_t::edit_alpha(uint8_t alpha)
	{
		m_alpha = alpha;
		SDL_SetTextureAlphaMod(m_texture.get_raw(), alpha);
	}

	void text_t::edit_position(const SDL_Point& pos)
	{
		m_dst.x = pos.x;
		m_dst.y = pos.y;
	}

	void text_t::edit_position(int x, int y)
	{
		m_dst.x = x;
		m_dst.y = y;
	}

	void text_t::edit_font(font_t& font)
	{
		m_font = nullptr;
		m_font = &font;

		SDL_Texture*& tex = m_texture.get_raw();
		if (tex != nullptr)
		{
			SDL_DestroyTexture(tex);
			tex = nullptr;
		}

		if (m_message.length() == 0)
		{
			return;
		}

		int text_width;
		int text_height;
		SDL_Surface* surface;

		surface = TTF_RenderText_Blended(m_font->get_raw(), m_message.c_str(), m_color);
		tex = SDL_CreateTextureFromSurface(g_renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		SDL_FreeSurface(surface);

		SDL_SetTextureAlphaMod(tex, m_alpha);

		m_dst.w = text_width;
		m_dst.h = text_height;
	}

	void text_t::edit_font(const std::string& filepath, int size)
	{
		m_font->change_font(filepath, size);

		SDL_Texture*& tex = m_texture.get_raw();
		if (tex != nullptr)
		{
			SDL_DestroyTexture(tex);
			tex = nullptr;
		}

		if (m_message.length() == 0)
		{
			return;
		}

		int text_width;
		int text_height;
		SDL_Surface* surface;

		surface = TTF_RenderText_Blended(m_font->get_raw(), m_message.c_str(), m_color);
		tex = SDL_CreateTextureFromSurface(g_renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		SDL_FreeSurface(surface);

		SDL_SetTextureAlphaMod(tex, m_alpha);

		m_dst.w = text_width;
		m_dst.h = text_height;
	}

	void text_t::edit_color(const color_t& color)
	{
		m_color = color;
	}

	void text_t::edit(const std::string& message, const color_t& color, font_t& font, uint8_t alpha, std::optional<SDL_Point> pos)
	{
		m_message = message;
		m_color = color;
		m_alpha = alpha;
		m_font = &font;

		if (pos.has_value()) // user put argument
		{
			SDL_Point pos_unwrapped = pos.value();
			m_dst.x = pos_unwrapped.x;
			m_dst.y = pos_unwrapped.y;
		}

		SDL_Texture*& tex = m_texture.get_raw();
		if (tex != nullptr)
		{
			SDL_DestroyTexture(tex);
			tex = nullptr;
		}

		if (m_message.length() == 0)
		{
			return;
		}

		int text_width;
		int text_height;
		SDL_Surface* surface;

		surface = TTF_RenderText_Blended(m_font->get_raw(), message.c_str(), color);
		tex = SDL_CreateTextureFromSurface(g_renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		SDL_FreeSurface(surface);

		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(tex, alpha);

		m_dst.w = text_width;
		m_dst.h = text_height;
	}

	void text_t::render()
	{
		SDL_Rect dst = m_dst.c_rec(); // since sdl_rendercopy() doesnt change the dst values irdgaf ill just copy it every call
		if (flip == SDL_FLIP_NONE)
		{
			SDL_RenderCopy(g_renderer, m_texture.get_raw(), NULL, &dst); 
		}
		else 
		{
			SDL_RenderCopyEx(g_renderer, m_texture.get_raw(), NULL, &dst, 0, nullptr, flip); 
		}
	}

	bool text_t::mouse_hovered()
	{
		return mouse::hovered(m_dst);
	}

	bool text_t::left_clicked()
	{
		return mouse::clicked_left(m_dst);
	}

	bool text_t::right_clicked()
	{
		return mouse::clicked_right(m_dst);
	}

	const std::string text_t::get_message() const
	{
		return m_message;
	}

	rect_t text_t::get_dst() const
	{
		return m_dst;
	}

	color_t text_t::get_color() const
	{
		return m_color;
	}

	uint8_t text_t::get_alpha() const
	{
		return m_alpha;
	}
}