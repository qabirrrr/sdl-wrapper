#include "../../include/asset"
#include "../../include/globals"
#include "../../include/sdl++"

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

		void background_t::render(uint8_t alpha, SDL_RendererFlip flip)
		{
			if (flip == SDL_FLIP_NONE)
			{
				m_texture.render(m_source, m_destination, alpha);
			}
			else
			{
				m_texture.render(m_source, m_destination, alpha, flip);
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
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
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
			x = dst.x;
			y = dst.y;
			w = dst.w;
			h = dst.h;
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
			x = dst.x;
			y = dst.y;
			w = dst.w;
			h = dst.h;
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




		void spritesheet_t::insert_spritesheet(texture_t& texture)
		{
			m_texture = &texture;
		}

		void spritesheet_t::render(uint8_t alpha)
		{
			x += vel_x;
			y += vel_y;

			m_destination.x = x;
			m_destination.y = y;
			m_destination.w = w;
			m_destination.h = h;

			if (flip == SDL_FLIP_NONE)
			{
				m_texture->render(m_source, m_destination, alpha);
			}
			else
			{
				m_texture->render(m_source, m_destination, alpha, flip);
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

		void spritepack_t::render(uint8_t alpha)
		{
			x += vel_x;
			y += vel_y;

			m_destination.x = x;
			m_destination.y = y;
			m_destination.w = w;
			m_destination.h = h;

			if (flip == SDL_FLIP_NONE)
			{
				m_textures[animation_index].render(m_source, m_destination, alpha);
			}
			else
			{
				m_textures[animation_index].render(m_source, m_destination, alpha, flip);
			}
		}

	}
}