#include "../../include/font"
#include <iostream>

namespace sdl
{
    font_t::font_t(const std::string& filepath, int size)
	{
		load_font(filepath, size);
	}

	font_t::~font_t()
	{
		TTF_CloseFont(m_ttf_font);
		m_ttf_font = nullptr;
	}

	font_t::font_t(font_t&& old) noexcept
	{
		m_ttf_font = old.m_ttf_font;
		old.m_ttf_font = nullptr;
	}

	font_t& font_t::operator=(font_t&& old) noexcept 
	{
		if (this != &old)
		{
			if (m_ttf_font) TTF_CloseFont(m_ttf_font);
			m_ttf_font = old.m_ttf_font;
			old.m_ttf_font = nullptr;
		}
		return *this;
	}

	void font_t::load_font(const std::string& filepath, int size)
	{
		m_ttf_font = TTF_OpenFont(filepath.c_str(), size);
		if (!m_ttf_font)
		{
			std::cout << "Error (Font): " << TTF_GetError() << '\n';
		}
	}

	void font_t::change_font(const std::string& filepath, int size)
	{
		if (m_ttf_font)
		{
			TTF_CloseFont(m_ttf_font);
			m_ttf_font = nullptr;
		}
		load_font(filepath, size);
	}

	TTF_Font* font_t::get_raw()
	{
		return m_ttf_font;
	}
}