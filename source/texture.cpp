#include "../../include/texture"
#include "../../include/globals"
#include <iostream>

namespace sdl 
{
    texture_t::texture_t(const std::string& filepath)
	{
		load(filepath);
	}

	texture_t::~texture_t()
	{
		SDL_DestroyTexture(m_sdl_texture);
	}

	texture_t::texture_t(texture_t&& old) noexcept
	{
		m_sdl_texture = old.m_sdl_texture;
		m_filepath = std::move(old.m_filepath);
		old.m_sdl_texture = nullptr;
		
	}

	texture_t& texture_t::operator=(texture_t&& old) noexcept 
	{
		if (this != &old)
		{
			if (m_sdl_texture) SDL_DestroyTexture(m_sdl_texture);
			m_sdl_texture = old.m_sdl_texture;
			m_filepath = std::move(old.m_filepath);
			old.m_sdl_texture = nullptr;
		}
		return *this;
	}

	void texture_t::load(const std::string& filepath)
	{
		m_filepath = filepath;
		if (m_sdl_texture)
		{
			SDL_DestroyTexture(m_sdl_texture);
			m_sdl_texture = nullptr;
		}
		m_sdl_texture = IMG_LoadTexture(g_renderer, filepath.c_str());
		if (m_sdl_texture == nullptr)
		{
			if (g_textures_loaded)
			{
				std::cout << "Failed to load textures\n";
				g_textures_loaded = false;
			}
			std::cout << "Error: " << IMG_GetError() << '\n';
		}
		SDL_SetTextureBlendMode(m_sdl_texture, SDL_BLENDMODE_BLEND);
	}

	void texture_t::change(texture_t& texture)
	{
		m_filepath = texture.get_filepath();
		if (m_sdl_texture)
		{
			SDL_DestroyTexture(m_sdl_texture);
			m_sdl_texture = nullptr;
		}
		m_sdl_texture = texture.get_raw();
	}

	const std::string texture_t::get_filepath()
	{
		return m_filepath;
	}


	void texture_t::render(const SDL_Rect& src, const SDL_Rect& dst, uint8_t alpha, SDL_RendererFlip flip)
	{
		if (flip == SDL_FLIP_NONE)
		{
			SDL_RenderCopy(g_renderer, m_sdl_texture, &src, &dst);
			SDL_SetTextureAlphaMod(m_sdl_texture, alpha);
		}
		else
		{
			SDL_RenderCopyEx(g_renderer, m_sdl_texture, &src, &dst, 0, NULL, flip);
			SDL_SetTextureAlphaMod(m_sdl_texture, alpha);
		}
	}

	void texture_t::render(const rect_t& src, const rect_t& dst, uint8_t alpha, SDL_RendererFlip flip)
	{
		// how ugly this is, is beginning to piss me off. pls change this eventually
		SDL_Rect s = src.c_rec();
		SDL_Rect d = dst.c_rec();
		if (flip == SDL_FLIP_NONE)
		{
			SDL_RenderCopy(g_renderer, m_sdl_texture, &s, &d);
		}
		else
		{
			SDL_RenderCopyEx(g_renderer, m_sdl_texture, &s, &d, 0, NULL, flip);
		}
	}

	SDL_Texture*& texture_t::get_raw()
	{
		return m_sdl_texture;
	}
}