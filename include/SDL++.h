#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <optional>

namespace sdl
{
	struct color_t : public SDL_Color
	{
		bool operator==(const color_t& other) const;
	};

	namespace colors
	{
		const color_t BLACK = { 0, 0, 0, 255 };
		const color_t WHITE = { 255, 255, 255, 255 };
		const color_t RED = { 255, 0, 0, 255 };
		const color_t GREEN = { 0, 255, 0, 255 };
		const color_t BLUE = { 0, 0, 255, 255 };
		const color_t YELLOW = { 255, 255, 0, 255 };
		const color_t CYAN = { 0, 255, 255, 255 };
		const color_t MAGENTA = { 255, 0, 255, 255 };
		const color_t GRAY = { 128, 128, 128, 255 };
		const color_t ORANGE = { 255, 165, 0, 255 };
		const color_t BROWN = { 139,  69,  19, 255 };
		const color_t PINK = { 255, 192, 203, 255 };
		const color_t PURPLE = { 128, 0, 128, 255 };
		const color_t VIOLET = { 238, 130, 238, 255 };
		const color_t INDIGO = { 75, 0, 130, 255 };
		const color_t GOLD = { 255, 215, 0, 255 };
		const color_t SILVER = { 192, 192, 192, 255 };
		const color_t MAROON = { 128, 0, 0, 255 };
		const color_t OLIVE = { 128, 128, 0, 255 };
		const color_t TEAL = { 0, 128, 128, 255 };
		const color_t NAVY = { 0, 0, 128, 255 };
		const color_t LAVENDER = { 230, 230, 250, 255 };
		const color_t BEIGE = { 245, 245, 220, 255 };
		const color_t TURQUOISE = { 64, 224, 208, 255 };
		const color_t SALMON = { 250, 128, 114, 255 };
		const color_t CRIMSON = { 220,  20,  60, 255 };
		const color_t CORAL = { 255, 127,  80, 255 };
		const color_t MINT = { 189, 252, 201, 255 };
		const color_t PEACH = { 255, 218, 185, 255 };
		const color_t CHARTREUSE = { 127, 255, 0, 255 };
		const color_t AQUAMARINE = { 127, 255, 212, 255 };
		const color_t LIME = { 0, 255, 0, 255 };
		const color_t TOMATO = { 255,  99,  71, 255 };
		const color_t WHEAT = { 245, 222, 179, 255 };	

		// Returns a vector of primary colors
		std::vector<color_t> get_primary();

		// Returns a vector of secondary colors
		std::vector<color_t> get_secondary();

		// Returns a vector of both primary and colors
		std::vector<color_t> get_foundational();

		// Returns a vector of all the colors
		std::vector<color_t> get_all();
	};

	struct rect_t
	{
		int x, y;
		int w, h;

		rect_t() = default;
		rect_t(int x, int y, int w, int h, color_t color = colors::BLACK);

		bool operator==(const rect_t& other) const;

		// Edit the color of the rectangle
		void edit_color(const color_t& color);

		// Edit the properties of the rectangle
		void edit_properties(int x, int y, int w, int h);

		// Renders rectangle outline to renderer
		void render_outline(uint8_t alpha = 255);

		// Renders rectangle fill to renderer
		void render_fill(uint8_t alpha = 255);

		// Mouse hovered over rectangle
		bool mouse_hovered();

		// Mouse left clicked over rectangle
		bool left_clicked();

		// Mouse right clicked over rectangle
		bool right_clicked();

		// Rectangle collided with a type Rect
		bool collided_width(const rect_t& rect) const;

		// Rectangle collided with a type SDL_Rect
		bool collided_with(const SDL_Rect& rect) const;

		// Converts type rect to SDL_Rect 
		SDL_Rect c_rec() const;

	private:
		color_t m_color;
	};

	struct texture_t
	{
		texture_t() = default;
		texture_t(const std::string& filepath);
		~texture_t();

		texture_t(const texture_t&) = delete; 
		texture_t& operator=(const texture_t&) = delete; 

		texture_t(texture_t&& old) noexcept;
		texture_t& operator=(texture_t&& old) noexcept;

		// Load the texture as a chosen image
		//\param filepath The filepath to the image
		void load(const std::string& filepath);

		// Change texture
		//\param texture The texture
		void change(texture_t& texture);

		// Get the filepath
		const std::string get_filepath();

		// Render the texture onto screen with the option to flip it 
		//\param src Properties of the source image
		//\param dst Properties of the image to be rendered on screen
		//\param alpha Alpha value for transparency
		//\param flip Variable that tracks when a flip occurs 
		void render(const SDL_Rect& src, const SDL_Rect& dst, uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Render the texture onto screen with the option to flip it 
		//\param src Properties of the source image
		//\param dst Properties of the image to be rendered on screen
		//\param alpha Alpha value for transparency
		//\param flip Variable that tracks when a flip occurs 
		void render(const rect_t& src, const rect_t& dst, uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Get the raw SDL_Texture*
		SDL_Texture*& get_raw();

	private:
		SDL_Texture* m_sdl_texture = nullptr;
		std::string m_filepath;
	};

	struct font_t
	{
		font_t() = default;
		font_t(const std::string& filepath, int size);
		~font_t();

		font_t(const font_t&) = delete; 
		font_t& operator=(const font_t&) = delete; 

		font_t(font_t&& old) noexcept;
		font_t& operator=(font_t&& old) noexcept;

		// Load font
		void load_font(const std::string& filepath, int size);

		// Change font
		void change_font(const std::string& filepath, int size);

		// Get the raw TTF_Font* 
		TTF_Font* get_raw();
		
	private:
		TTF_Font* m_ttf_font = nullptr;
	};

	struct text_t
	{
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		text_t() = default;
		text_t(const std::string& message, const color_t& color, font_t& font, uint8_t alpha = 255, SDL_Point pos = {0,0});
		~text_t() = default;

		text_t(const text_t&) = delete; 
		text_t& operator=(const text_t&) = delete; 

		text_t(text_t&& old) noexcept;
		text_t& operator=(text_t&& old) noexcept;

		/* Create a piece of text
		*
		* \param message The text to be displayed
		* \param pos The x, y coordinates 
		* \param color The color 
		* \param font The font 
		* \param alpha Alpha value for transparency
		*/
		void create(const std::string& message, const color_t& color, font_t& font, uint8_t alpha = 255, SDL_Point pos = {0,0});

		// Edit the displayed text
		// \param message The text message 
		void edit_message(const std::string& message);

		// Edit the blend transparency
		// \param The alpha value for transparency
		void edit_alpha(uint8_t alpha);

		// Edit the text position
		// \param The `x`, `y` coordinates 
		void edit_position(const SDL_Point& pos);

		// Edit the text position
		// \param The `x`, `y` coordinates 
		void edit_position(int x, int y);

		// Edit the text font
		// \param The font
		void edit_font(font_t& font);

		// Edit the text font
		// \param The font details
		void edit_font(const std::string& filepath, int size);

		// Edit the color
		// \param color The color
		void edit_color(const color_t& color);

		/* Edit the position, color, the displayed text and alpha value
		* \param message The text to be displayed
		* \param pos The x, y coordinates 
		* \param color The color 
		* \param font The font 
		* \param alpha Alpha value for transparency
		*/
		void edit(const std::string& message, const color_t& color, font_t& font, uint8_t alpha = 255, std::optional<SDL_Point> pos = std::nullopt);

		// Render the text
		void render();

		// Check if the mouse hovered over the asset
		bool mouse_hovered();

		// Check if the mouse left clicked over the asset
		bool left_clicked();

		// Check if the mouse right clicked over the asset
		bool right_clicked();

		// Get message of text
		const std::string get_message() const;

		// Get destination values of text
		rect_t get_dst() const;

		// Get color of text
		color_t get_color() const;

		// Get alpha value of text
		uint8_t get_alpha() const;

	private:
		std::string m_message;
		texture_t m_texture;
		font_t* m_font = nullptr;
		rect_t m_dst;
		color_t m_color;
		uint8_t m_alpha;
	};

	namespace asset
	{
		// Bckgrounds or overlays that cover the entire screen
		struct background_t
		{
			background_t();
			background_t(const std::string& filepath);

			background_t(const background_t&) = delete;
			background_t& operator = (const background_t&) = delete;
			
			background_t(background_t&& old) noexcept = default;
			background_t& operator = (background_t&& old) noexcept = default;

			// Load the texture as a chosen image
			//\param filepath The filepath to the image
			void load_texture(const std::string& filepath);

			// Render the texture onto screen with the option to flip it 
			//\param alpha Alpha value for transparency
			//\param flip Variable that tracks when a flip occurs 
			void render(uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		private:
			texture_t m_texture;
			rect_t m_source;
			rect_t m_destination;
		};

		struct asset_t
		{
			int x, y;
			int w, h;
			float vel_x = 0.0f;
			float vel_y = 0.0f;
			SDL_RendererFlip flip = SDL_FLIP_NONE;

			asset_t() = default;

			asset_t(const asset_t&) = delete;
			asset_t& operator = (const asset_t&) = delete;
			
			asset_t(asset_t&& old) noexcept = default;
			asset_t& operator = (asset_t&& old) noexcept = default;

			// Set the src values of the image
			//\param x The x coordinate of the image source
			//\param y The y coordinate of the image source
			//\param w The width of the image source
			//\param h The height of the image source
			void set_src(int x, int y, int w, int h);

			// Set the dst values of the image 
			//\param x The x coordinate of the image destination
			//\param y The y coordinate of the image destination
			//\param w The width of the image destination
			//\param h The height of the image destination
			void set_dst(int x, int y, int w, int h);

			// Set the src values of the image
			void set_src(const SDL_Rect& src);

			// Set the dst values of the image 
			void set_dst(const SDL_Rect& dst);

			// Set the src values of the image
			void set_src(const rect_t& src);

			// Set the dst values of the image 
			void set_dst(const rect_t& dst);

			// Get the asset's src values 
			rect_t get_src() const;

			// Get the asset's dst values 
			rect_t get_dst() const;

			// Check if the mouse hovered over the asset
			bool mouse_hovered();

			// Check if the mouse left clicked over the asset
			bool left_clicked();

			// Check if the mouse right clicked over the asset
			bool right_clicked();

			// Rectangle collided with a type asset_t
			bool collided_with(const asset_t& asset);

			// Rectangle collided with a type rect_t
			bool collided_with(const rect_t& rect);

			// Rectangle collided with a type SDL_Rect
			bool collided_with(const SDL_Rect& rect);

		protected:
			rect_t m_source;
			rect_t m_destination;
		};

		// This is best for animations stored in a singular spritesheet.
		struct spritesheet_t : public asset_t
		{
			// Insert the texture
			//\param texture The texture
			void insert_spritesheet(texture_t& texture);

			// Render the entity's texture onto screen 
			//\param alpha Alpha value for transparency 
			void render(uint8_t alpha = 255);

		private:
			texture_t* m_texture = nullptr;
		};

		// This is best for animations stored in numerous sprite files
		struct spritepack_t : public asset_t
		{
			int animation_index = 0;

			// Add a texture as a chosen image
			//\param filepath The filepath to the image
			void add_sprite(const std::string& filepath);

			// Delete the animation
			void delete_spritepack();

			// Assign an animation
			void insert_spritepack(std::vector<texture_t>& animation);
			
			// Render the entity's texture onto screen 
			//\param alpha Alpha value for transparency 
			void render(uint8_t alpha = 255);

		private:
			std::vector<texture_t> m_textures;
		};


	};


	namespace render
	{
		// Clear garbage left behind from the renderer
		void clear();

		// Display everything from the renderer to the screen
		void present();

		// Render a color to the renderer
		void color(const color_t& color);
	};

	namespace mouse
	{
		// Check if the mouse hovered over any rectangle
		bool hovered(const SDL_Rect& rect);

		// Check if the mouse left clicked on any rectangle 
		bool clicked_left(const SDL_Rect& rect);

		// Check if the mouse right clicked on any rectangle 
		bool clicked_right(const SDL_Rect& rect);


		// Check if the mouse hovered over any rectangle
		bool hovered(const rect_t& rect);

		// Check if the mouse left clicked on any rectangle 
		bool clicked_left(const rect_t& rect);

		// Check if the mouse right clicked on any rectangle 
		bool clicked_right(const rect_t& rect);
	};

	namespace keys
	{
		// Call update at the very end of game loop 
		// By right though, `sdl::update()` should be called as it covers everything
		// Unless there is an apparent need to only call `keys::update()` and not `sdl::update()`
		void update();

		// Check if key is pressed
		// `keys::update()` must be called for this to be properly tracked
		bool pressed(SDL_Scancode key);

		// Check if key is released
		// `keys::update()` must be called for this to be properly tracked
		bool released(SDL_Scancode key);

		// Check if key is being held
		bool held(SDL_Scancode key);
	};

	namespace audio
	{
		struct sound_t
		{
			sound_t() = default;
			sound_t(const std::string& filepath, int channel);
			~sound_t();

			sound_t(const sound_t&) = delete; 
			sound_t& operator=(const sound_t&) = delete; 

			sound_t(sound_t&& old) noexcept;
			sound_t& operator=(sound_t&& old) noexcept;

			// Load the sound
			void load_sound(const std::string& filepath);

			// Get filepath
			const std::string get_filepath();

			// Change channel (-1 by default)
			// Note that the change only happens the next time you call `sdl::audio::sound::play()`, whatever was being played before this function call will stay in that channel
			void change_channel(int channel);

			// Check if the channel it is assigned to is currently playing
			bool channel_is_playing();

			// Adjust volume (128 by default)
			void adjust_volume(int volume);

			// Get the channel sound is current being played in
			int get_channel() const;

			// Get current volume
			int get_volume() const;

			// Check if sound is currently paused
			bool is_paused();

			// Play the sound
			void play(int loops = 0);

			// Stop the sound
			void stop();

			// Pause the sound
			void pause();

			// Resume the sound
			void resume();

		private:
			Mix_Chunk* m_sound = nullptr;
			int m_channel = -1;
			int m_volume = 128;
			std::string m_filepath;
			bool m_paused = false; 

		};

		struct music_t
		{
			music_t() = default;
			music_t(const std::string& filepath);
			~music_t();

			music_t(const music_t&) = delete; 
			music_t& operator=(const music_t&) = delete; 

			music_t(music_t&& old) noexcept;
			music_t& operator=(music_t&& old) noexcept;

			// Load the music
			void load_music(const std::string& filepath);

			// Get filepath
			std::string get_filepath();

			// Play the music if not already playing
			void play(int loops = 0);

			// Adjust volume (128 by default)
			void adjust_volume(int volume);

			// Get current volume
			int get_volume() const;

			// Check if music is currently on track 
			// Whether it is paused is irrelevant, this solely checks if it is the current track on.
			bool is_on();

			// Check if music is currently paused
			bool is_paused();

			// Stop the music
			void stop();

			// Pause the music
			void pause();

			// Resume the music
			void resume();

		private:
			Mix_Music* m_music = nullptr;
			int m_volume = 128;
			std::string m_filepath; 
			bool m_paused = false; 
		};
	}

	// Initialize all the resources for SDL2 API
	void init(const std::string& title, int width, int height, Uint32 flags);

	// Destroy and clean up all the resources for SDL2 API
	void cleanup();

	// Call core event handling at the very start of the game loop
	void handle_events();

	// Check collisions between 2 rectangles
	bool check_collisions(const SDL_Rect& rectA, const SDL_Rect& rectB);

	// Check collisions between 2 rectangles
	bool check_collisions(const rect_t& rectA, const rect_t& rectB);

	// Check what the ASCII character user typed
	std::string get_character_input();

	// Check if the user entered a character
	bool character_is_typed();

	// Returns `true` if all textures loaded, otherwise `false`
	bool textures_loaded();

	// Check if left clicked
	// `sdl::handle_events()` must be called for this to be properly tracked
	bool left_clicked();

	// Check if right clicked
	// `sdl::handle_events()` must be called for this to be properly tracked
	bool right_clicked();

	// Returns mouse `x`, `y` coordinates
	// `sdl::handle_events()` must be called for this to be properly tracked
	SDL_Point get_mousepos();

	// Returns `true` if SDL2 is running, otherwise `false`
	// `sdl::handle_events()` must be called for this to be properly tracked
	// Use this for game loop.
	// `while (sdl::running()) {}`
	bool running();

	// Call core update at the very end of the game loop
	void update();

	// Returns the game renderer
	// Only call if you want to do something explicitly with the renderer itself
	// Otherwise, this method should preferably never be called
	// Do not destroy the renderer during the lifetime of this application
	SDL_Renderer* get_renderer();
};
