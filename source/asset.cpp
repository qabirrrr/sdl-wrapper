#include "../../include/asset"
#include "../../include/globals"
#include "../../include/sdl++"
#include <memory>
#include <iostream>

namespace sdl 
{
    namespace asset 
	{
		background_t::background_t()
		{
			m_source = { 0, 0, g_width, g_height };
			m_destination = { 0, 0, g_width, g_height };
		}

		background_t::background_t(const std::string& filepath)
		{
			m_source = { 0, 0, g_width, g_height };
			m_destination = { 0, 0, g_width, g_height };
			load_texture(filepath);
		}

		void background_t::load_texture(const std::string& filepath)
		{
			m_texture.load(filepath);
		}

		void background_t::edit_alpha(uint8_t alpha)
		{
			m_alpha = alpha;
			m_texture.edit_alpha(alpha);
		}

		uint8_t background_t::get_alpha()
		{
			return m_alpha;
		}

		void background_t::render(SDL_RendererFlip flip)
		{
			if (flip == SDL_FLIP_NONE)
			{
				m_texture.render(m_source, m_destination);
			}
			else
			{
				m_texture.render(m_source, m_destination, flip);
			}
		}




		void asset_t::set_src(int x, int y, int w, int h)
		{
			m_source.x = x;
			m_source.y = y;
			m_source.w = w;
			m_source.h = h;
		}

		void asset_t::set_dst(int x, int y, int w, int h)
		{
			m_destination.x = x;
			m_destination.y = y;
			m_destination.w = w;
			m_destination.h = h;
		}

		void asset_t::set_src(const SDL_Rect& src)
		{
			m_source.x = src.x;
			m_source.y = src.y;
			m_source.w = src.w;
			m_source.h = src.h;
		}

		void asset_t::set_dst(const SDL_Rect& dst)
		{
			m_destination.x = dst.x;
			m_destination.y = dst.y;
			m_destination.w = dst.w;
			m_destination.h = dst.h;
		}

		void asset_t::set_src(const rect_t& src)
		{
			m_source.x = src.x;
			m_source.y = src.y;
			m_source.w = src.w;
			m_source.h = src.h;
		}

		void asset_t::set_dst(const rect_t& dst)
		{
			m_destination.x = dst.x;
			m_destination.y = dst.y;
			m_destination.w = dst.w;
			m_destination.h = dst.h;
		}

		void asset_t::set_x(int x)
		{
			m_destination.x = x;
		}

		void asset_t::set_y(int y)
		{
			m_destination.y = y;
		}

		void asset_t::set_w(int w)
		{
			m_destination.w = w;
		}

		void asset_t::set_h(int h)
		{
			m_destination.h = h;
		}

		rect_t asset_t::get_src() const
		{
			return m_source;
		}

		rect_t asset_t::get_dst() const
		{
			return m_destination;
		}

		bool asset_t::mouse_hovered()
		{
			return mouse::hovered(m_destination);
		}

		bool asset_t::left_clicked()
		{
			return mouse::left_clicked(m_destination);
		}

		bool asset_t::right_clicked()
		{
			return mouse::right_clicked(m_destination);
		}

		bool asset_t::collided_with(const asset_t& asset)
		{
			return check_collisions(m_destination.c_rec(), (asset.get_dst()).c_rec());
		}

		bool asset_t::collided_with(const rect_t& rect)
		{
			return rect.collided_with(m_destination.c_rec());
		}

		bool asset_t::collided_with(const SDL_Rect& rect)
		{
			return check_collisions(m_destination.c_rec(), rect);
		}


		spritesheet_t::~spritesheet_t()
		{
			if (m_allocated)
			{
				delete m_texture;
				m_allocated = false;
			}
			m_texture = nullptr;
		}

		void spritesheet_t::load(const std::string& filepath)
		{
			if (!m_texture)
			{
				m_texture = new texture_t();
				m_allocated = true;
			}
				
			m_texture->load(filepath);
		}

		void spritesheet_t::edit_alpha(uint8_t alpha)
		{
			m_alpha = alpha;
			m_texture->edit_alpha(alpha);
		}

		uint8_t spritesheet_t::get_alpha()
		{
			return m_alpha;
		}

		void spritesheet_t::insert_spritesheet(texture_t& texture)
		{
			if (m_texture)
			{
				if (m_allocated)
				{
					delete m_texture;
					m_allocated = false;
				}
				m_texture = nullptr;
			}
			m_texture = &texture;
		}


		// The pointer logic in this struct is unsafe asf
		// Just dont be a dumb bitch and call this when m_texture is null and all should be good
		void spritesheet_t::render(std::optional<uint8_t> alpha)
		{
			m_destination.x += vel_x;
			m_destination.y += vel_y;

			if (alpha.has_value())
			{
				edit_alpha(alpha.value());
			}

			if (flip == SDL_FLIP_NONE)
			{
				m_texture->render(m_source, m_destination);
			}
			else
			{
				m_texture->render(m_source, m_destination, flip);
			}
		}




		void spritepack_t::add_sprite(const std::string& filepath)
		{
			m_textures.emplace_back(filepath);
		}

		void spritepack_t::delete_spritepack()
		{
			m_textures.clear();  
		}

		void spritepack_t::insert_spritepack(std::vector<texture_t>& animation)
		{
			delete_spritepack();
			for (texture_t& frame : animation)
			{
				add_sprite(frame.get_filepath());
			}
		}

		void spritepack_t::edit_alpha(uint8_t alpha) // test this out, havent tried it out to see if it works.
		{
			m_alpha = alpha;
			for (texture_t& frame : m_textures)
			{
				frame.edit_alpha(alpha);
			}
		}

		uint8_t spritepack_t::get_alpha()
		{
			return m_alpha;
		}

		void spritepack_t::render(std::optional<uint8_t> alpha)
		{
			m_destination.x += vel_x;
			m_destination.y += vel_y;

			if (alpha.has_value())
			{
				edit_alpha(alpha.value());
			}

			if (flip == SDL_FLIP_NONE)
			{
				m_textures[animation_index].render(m_source, m_destination);
			}
			else
			{
				m_textures[animation_index].render(m_source, m_destination, flip);
			}
		}

	}
}