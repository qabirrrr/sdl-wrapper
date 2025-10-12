#include "../include/SDL++.h"
#include <iostream>
#include <cstring>
#include <optional>

namespace sdl
{
	SDL_Renderer* g_renderer;
	bool g_textures_loaded = true;
	bool g_running = true;

	bool g_left_clicked;
	bool g_right_clicked;
	SDL_Point g_mousepos;

	SDL_Window* g_window;
	int g_width;
	int g_height;
	Mix_Music* g_current_music;
	const uint8_t* g_current_keystate;
	uint8_t g_previous_keystate[SDL_NUM_SCANCODES] = {0};
	std::string g_character = "";
	bool g_char_typed = false;

	bool color_t::operator==(const color_t& other) const
	{
		return
		r == other.r &&
		g == other.g &&
		b == other.b;
	}

	namespace colors 
	{
		std::vector<color_t> get_primary()
		{
			std::vector<color_t> primary =
			{
				colors::RED,
				colors::YELLOW,
				colors::BLUE
			};
			return primary;
		}


		std::vector<color_t> get_secondary()
		{
			std::vector<color_t> secondary =
			{
				colors::ORANGE,
				colors::GREEN,
				colors::PURPLE,
			};
			return secondary;
		}

		std::vector<color_t> get_foundational()
		{
			std::vector<color_t> foundational =
			{
				colors::ORANGE,
				colors::RED,
				colors::GREEN,
				colors::YELLOW,
				colors::PURPLE,
				colors::BLUE
			};
			return foundational;
		}

		std::vector<color_t> get_all()
		{
			std::vector<color_t> all =
			{
				colors::BLACK,
				colors::WHITE,
				colors::RED,
				colors::GREEN,
				colors::BLUE,
				colors::YELLOW,
				colors::CYAN,
				colors::MAGENTA,
				colors::GRAY,
				colors::ORANGE,
				colors::BROWN,
				colors::PINK,
				colors::PURPLE,
				colors::VIOLET,
				colors::INDIGO,
				colors::GOLD,
				colors::SILVER,
				colors::MAROON,
				colors::OLIVE,
				colors::TEAL,
				colors::NAVY,
				colors::LAVENDER,
				colors::BEIGE,
				colors::TURQUOISE,
				colors::SALMON,
				colors::CRIMSON,
				colors::CORAL,
				colors::MINT,
				colors::PEACH,
				colors::CHARTREUSE,
				colors::AQUAMARINE,
				colors::LIME,
				colors::TOMATO,
				colors::WHEAT
			};
			return all;
		}
	}




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
		// i do not care. this will not heavily affect performance. yes i know this is bad
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

	void text_t::create(const std::string& message, const color_t& color, font_t& font, uint8_t alpha, SDL_Point pos)
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
			return mouse::clicked_left(m_destination);
		}

		bool asset_t::right_clicked()
		{
			return mouse::clicked_right(m_destination);
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



	
	
	namespace keys
	{
		void copy_key(uint8_t* dst, const uint8_t* src) 
		{
			std::memcpy(dst, src, SDL_NUM_SCANCODES * sizeof(uint8_t));
		}

		void update()
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



	
	namespace audio
	{
		sound_t::sound_t(const std::string& filepath, int channel)
		{
			load_sound(filepath);
			m_channel = channel;
		}

		sound_t::~sound_t()
		{
			Mix_FreeChunk(m_sound);
		}

		sound_t::sound_t(sound_t&& old) noexcept
		{
			m_sound = old.m_sound; 
			m_channel = old.m_channel;
			m_volume = old.m_volume;
			m_filepath = std::move(old.m_filepath);
			old.m_sound = nullptr;
		}

		sound_t& sound_t::operator=(sound_t&& old) noexcept 
		{
			if (this != &old)
			{
				if (m_sound) Mix_FreeChunk(m_sound);
				m_sound = old.m_sound; 
				m_channel = old.m_channel;
				m_volume = old.m_volume;
				m_filepath = std::move(old.m_filepath);
				old.m_sound = nullptr;
			}
			return *this;
		}

		void sound_t::load_sound(const std::string& filepath)
		{
			m_filepath = filepath;
			m_sound = Mix_LoadWAV(m_filepath.c_str());
			if (m_sound == nullptr)
			{
				std::cout << "Error (Loading sound): " << Mix_GetError() << '\n';
			}
		}

		const std::string sound_t::get_filepath()
		{
			return m_filepath;
		}

		void sound_t::change_channel(int channel)
		{
			m_channel = channel;
		}

		bool sound_t::channel_is_playing()
		{
			if (Mix_Playing(m_channel))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void sound_t::adjust_volume(int volume)
		{
			if (volume >= 0 && volume <= 128) m_volume = volume;
			Mix_VolumeChunk(m_sound, volume);
		}

		int sound_t::get_channel() const
		{
			return m_channel;
		}

		int sound_t::get_volume() const
		{
			return m_volume;
		}

		bool sound_t::is_paused()
		{
			return m_paused;
		}


		void sound_t::play(int loops)
		{
			Mix_PlayChannel(m_channel, m_sound, loops); 
		}

		void sound_t::stop()
		{
			Mix_HaltChannel(m_channel);
		}

		void sound_t::pause()
		{
			Mix_Pause(m_channel);
			m_paused = true;
		}

		void sound_t::resume()
		{
			Mix_Resume(m_channel);
			m_paused = false;
		}




		music_t::music_t(const std::string& filepath)
		{
			load_music(filepath);
		}

		music_t::music_t(music_t&& old) noexcept
		{
			m_music = old.m_music; 
			m_volume = old.m_volume;
			m_filepath = std::move(old.m_filepath);
			old.m_music = nullptr;
		}

		music_t& music_t::operator=(music_t&& old) noexcept 
		{
			if (this != &old)
			{
				if (m_music) Mix_FreeMusic(m_music);
				m_music = old.m_music;
				m_volume = old.m_volume;
				m_filepath = std::move(old.m_filepath);
				old.m_music = nullptr;
			}
			return *this;
		}

		void music_t::load_music(const std::string& filepath)
		{
			m_filepath = filepath;
			m_music = Mix_LoadMUS(m_filepath.c_str());
			if (m_music == nullptr)
			{
				std::cout << "Error (Loading music): " << Mix_GetError() << '\n';
			}
		}

		std::string music_t::get_filepath()
		{
			return m_filepath;
		}

		void music_t::adjust_volume(int volume)
		{
			m_volume = volume;
			Mix_VolumeMusic(volume);
		}

		int music_t::get_volume() const
		{
			return m_volume;
		}

		bool music_t::is_on()
		{
			if (g_current_music != m_music || Mix_PlayingMusic() == 0)
			{
				return false;
			}
			else 
			{
				return true;
			}
		}

		bool music_t::is_paused()
		{
			return m_paused;
		}

		void music_t::play(int loops)
		{
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(m_music, loops);
				g_current_music = m_music;
			}
		}

		void music_t::stop()
		{
			Mix_HaltMusic();
			g_current_music = nullptr;
		}

		void music_t::pause()
		{
			Mix_PauseMusic();
			m_paused = true;
		}

		void music_t::resume()
		{
			Mix_ResumeMusic();
			m_paused = false;
		}


		music_t::~music_t()
		{
			Mix_FreeMusic(m_music);
		}
	}




	void init(const std::string& title, int width, int height, Uint32 flags)
	{
		bool canInit = true;
		g_width = width;
		g_height = height;

		g_current_keystate = SDL_GetKeyboardState(NULL);

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			if (canInit)
			{
				std::cout << "API failed to load\n";
				canInit = false;
			}
			std::cout << "Error (SDL): " << SDL_GetError() << '\n';
		}

		if (TTF_Init())
		{
			if (canInit)
			{
				std::cout << "API failed to load\n";
				canInit = false;
			}
			std::cout << "Error (TTF): " << SDL_GetError() << '\n';
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			if (canInit)
			{
				std::cout << "API failed to load\n";
				canInit = false;
			}
			std::cout << "Error (Mixer): " << SDL_GetError() << '\n';
		}

		g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (g_window == nullptr)
		{
			if (canInit)
			{
				std::cout << "API failed to load\n";
				canInit = false;
			}
			std::cout << "Error (Window): " << SDL_GetError() << '\n';
		}

		Uint32 rf = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
		g_renderer = SDL_CreateRenderer(g_window, -1, rf);
		if (g_renderer == nullptr)
		{
			if (canInit)
			{
				std::cout << "API failed to load\n";
				canInit = false;
			}
			std::cout << "Error (Renderer): " << SDL_GetError() << '\n';
		}

		SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

		SDL_StartTextInput();
	}

	void cleanup()
	{
		SDL_StopTextInput();
		Mix_CloseAudio();
		Mix_Quit();
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(g_renderer);
		SDL_DestroyWindow(g_window);
	}

	void handle_events()
	{
		SDL_Event ev;
		g_left_clicked = false;
		g_right_clicked = false;
		g_char_typed = false;

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				g_running = false;
				break;
			}
			if (ev.type == SDL_TEXTINPUT)
			{
				g_character = ev.text.text;
				g_char_typed = true;
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
				{
					g_left_clicked = true;
				}
				if (ev.button.button == SDL_BUTTON_RIGHT)
				{
					g_right_clicked = true;
				}
			}
			SDL_GetMouseState(&g_mousepos.x, &g_mousepos.y);
		}

	}

	bool check_collisions(const SDL_Rect& rectA, const SDL_Rect& rectB)
	{
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = rectA.x;
		rightA = rectA.x + rectA.w;
		topA = rectA.y;
		bottomA = rectA.y + rectA.h;

		leftB = rectB.x;
		rightB = rectB.x + rectB.w;
		topB = rectB.y;
		bottomB = rectB.y + rectB.h;

		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		return true;
	}

	bool check_collisions(const rect_t& rectA, const rect_t& rectB)
	{
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = rectA.x;
		rightA = rectA.x + rectA.w;
		topA = rectA.y;
		bottomA = rectA.y + rectA.h;

		leftB = rectB.x;
		rightB = rectB.x + rectB.w;
		topB = rectB.y;
		bottomB = rectB.y + rectB.h;

		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		return true;
	}

	std::string get_character_input()
	{
		return g_character;
	}

	bool character_is_typed()
	{
		return g_char_typed;
	}

	bool textures_loaded()
	{
		return g_textures_loaded;
	}

	bool left_clicked()
	{
		return g_left_clicked;
	}

	bool right_clicked()
	{
		return g_right_clicked;
	}

	SDL_Point get_mousepos()
	{
		return g_mousepos;
	}

	bool running()
	{
		return g_running;
	}

	void update()
	{
		keys::update();
		g_character = "";
		SDL_Delay(1000 / 60);
	}

	SDL_Renderer* get_renderer()
	{
		return g_renderer;
	}


};






