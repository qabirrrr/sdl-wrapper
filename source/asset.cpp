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

		void background_t::set_src(int x, int y, int w, int h)
		{
			m_source.x = x;
			m_source.y = y;
			m_source.w = w;
			m_source.h = h;
		}

		void background_t::set_dst(int x, int y, int w, int h)
		{
			m_destination.x = x;
			m_destination.y = y;
			m_destination.w = w;
			m_destination.h = h;
		}

		rect_t background_t::get_src()
		{
			return m_source;
		}

		rect_t background_t::get_dst()
		{
			return m_destination;
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

		void asset_t::set_src_x(int x)
		{
			m_source.x = x;
		}

		void asset_t::set_src_y(int y)
		{
			m_source.y = y;
		}

		void asset_t::set_src_w(int w)
		{
			m_source.w = w;
		}

		void asset_t::set_src_h(int h)
		{
			m_source.h = h;
		}

		void asset_t::set_dst_x(int x)
		{
			m_destination.x = x;
		}

		void asset_t::set_dst_y(int y)
		{
			m_destination.y = y;
		}

		void asset_t::set_dst_w(int w)
		{
			m_destination.w = w;
		}

		void asset_t::set_dst_h(int h)
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


		static_texture_t::~static_texture_t()
		{
			if (m_allocated)
			{
				delete m_texture;
				m_allocated = false;
			}
			m_texture = nullptr;
		}

		void static_texture_t::load_texture(const std::string& filepath)
		{
			if (!m_texture)
			{
				m_texture = new texture_t();
				m_allocated = true;
			}
				
			m_texture->load(filepath);
		}

		void static_texture_t::edit_alpha(uint8_t alpha)
		{
			m_alpha = alpha;
			m_texture->edit_alpha(alpha);
		}

		uint8_t static_texture_t::get_alpha()
		{
			return m_alpha;
		}

		void static_texture_t::change_texture(texture_t& texture)
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
		void static_texture_t::render(std::optional<uint8_t> alpha)
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




		void dynamic_textures_t::add_texture(const std::string& filepath)
		{
			m_textures.emplace_back(filepath);
		}

		void dynamic_textures_t::delete_animation()
		{
			m_textures.clear();  
		}

		void dynamic_textures_t::assign_animation(std::vector<texture_t>& animation)
		{
			delete_animation();
			for (texture_t& frame : animation)
			{
				add_texture(frame.get_filepath());
			}
		}

		void dynamic_textures_t::edit_alpha(uint8_t alpha) // test this out, havent tried it out to see if it works.
		{
			m_alpha = alpha;
			for (texture_t& frame : m_textures)
			{
				frame.edit_alpha(alpha);
			}
		}

		void dynamic_textures_t::set_animation_index(int index)
		{
			m_animation_index = index;
		}

		int dynamic_textures_t::get_animation_index()
		{
			return m_animation_index;
		}	

		int dynamic_textures_t::get_animation_size()
		{
			return m_textures.size();
		}

		bool dynamic_textures_t::increment_animation_index()
		{
			if (m_animation_index < m_textures.size() - 1)
			{
				m_animation_index++;
				return true;
			}
			return false;
		}

		bool dynamic_textures_t::decrement_animation_index()
		{
			if (m_animation_index > 0)
			{
				m_animation_index--;
				return true;
			}
			return false;
		}


		uint8_t dynamic_textures_t::get_alpha()
		{
			return m_alpha;
		}

		void dynamic_textures_t::render(std::optional<uint8_t> alpha)
		{
			m_destination.x += vel_x;
			m_destination.y += vel_y;

			if (alpha.has_value())
			{
				edit_alpha(alpha.value());
			}

			if (flip == SDL_FLIP_NONE)
			{
				m_textures[m_animation_index].render(m_source, m_destination);
			}
			else
			{
				m_textures[m_animation_index].render(m_source, m_destination, flip);
			}
		}

	}
}