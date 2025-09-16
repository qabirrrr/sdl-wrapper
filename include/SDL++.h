#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

// TODOS BEFORE RELEASE:
// -> FIX : i can't make a vector of audios rn. probably the same for some of my other classes or structs
// -> Enable text input (e.g. user can write "abc" and I can detect the string "abc")

namespace sdl
{
	extern SDL_Renderer* renderer; // The game renderer
	extern bool all_textures_loaded; // Set to `true` if all textures loaded, otherwise `false`

	// Set to `true` if SDL2 is running, otherwise `false`
	// `sdl::handle_events()` must be called for this to be properly tracked
	// Use this for game loop.
	// `while (sdl::running) {}`
	extern bool running; 
						
	// Check if left clicked
	// `sdl::handle_events()` must be called for this to be properly tracked
	extern bool left_clicked; 

	// Check if right clicked
	// `sdl::handle_events()` must be called for this to be properly tracked
	extern bool right_clicked; 

	// Track mouse `x`, `y` coordinates
	// `sdl::handle_events()` must be called for this to be properly tracked
	extern SDL_Point mouse_pos; 

	namespace colors
	{
		const SDL_Color BLACK = { 0, 0, 0, 255 };
		const SDL_Color WHITE = { 255, 255, 255, 255 };
		const SDL_Color RED = { 255, 0, 0, 255 };
		const SDL_Color GREEN = { 0, 255, 0, 255 };
		const SDL_Color BLUE = { 0, 0, 255, 255 };
		const SDL_Color YELLOW = { 255, 255, 0, 255 };
		const SDL_Color CYAN = { 0, 255, 255, 255 };
		const SDL_Color MAGENTA = { 255, 0, 255, 255 };
		const SDL_Color GRAY = { 128, 128, 128, 255 };
		const SDL_Color ORANGE = { 255, 165, 0, 255 };
		const SDL_Color BROWN = { 139,  69,  19, 255 };
		const SDL_Color PINK = { 255, 192, 203, 255 };
		const SDL_Color PURPLE = { 128, 0, 128, 255 };
		const SDL_Color VIOLET = { 238, 130, 238, 255 };
		const SDL_Color INDIGO = { 75, 0, 130, 255 };
		const SDL_Color GOLD = { 255, 215, 0, 255 };
		const SDL_Color SILVER = { 192, 192, 192, 255 };
		const SDL_Color MAROON = { 128, 0, 0, 255 };
		const SDL_Color OLIVE = { 128, 128, 0, 255 };
		const SDL_Color TEAL = { 0, 128, 128, 255 };
		const SDL_Color NAVY = { 0, 0, 128, 255 };
		const SDL_Color LAVENDER = { 230, 230, 250, 255 };
		const SDL_Color BEIGE = { 245, 245, 220, 255 };
		const SDL_Color TURQUOISE = { 64, 224, 208, 255 };
		const SDL_Color SALMON = { 250, 128, 114, 255 };
		const SDL_Color CRIMSON = { 220,  20,  60, 255 };
		const SDL_Color CORAL = { 255, 127,  80, 255 };
		const SDL_Color MINT = { 189, 252, 201, 255 };
		const SDL_Color PEACH = { 255, 218, 185, 255 };
		const SDL_Color CHARTREUSE = { 127, 255, 0, 255 };
		const SDL_Color AQUAMARINE = { 127, 255, 212, 255 };
		const SDL_Color LIME = { 0, 255, 0, 255 };
		const SDL_Color TOMATO = { 255,  99,  71, 255 };
		const SDL_Color WHEAT = { 245, 222, 179, 255 };

		// Returns a vector of primary colors
		std::vector<SDL_Color> get_primary();

		// Returns a vector of secondary colors
		std::vector<SDL_Color> get_secondary();

		// Returns a vector of both primary and colors
		std::vector<SDL_Color> get_foundational();

		// Returns a vector of all the colors
		std::vector<SDL_Color> get_all();
	};

	class ttf
	{
	public:
		ttf() = default;
		ttf(const std::string message, SDL_Color color, TTF_Font* font, uint8_t alpha = 255, SDL_Point pos = {0,0});
		~ttf();

		/* Create a piece of text
		*
		* \param message The text to be displayed
		* \param pos The x, y coordinates of the text
		* \param color The color of the text
		* \param font The font (to be initialized manually)
		* \param alpha Alpha value for transparency
		*/
		void create(const std::string message, SDL_Color color, TTF_Font* font, uint8_t alpha = 255, SDL_Point pos = {0,0});

		// Get destination values of text
		// This only works after it's been created or edited. 
		SDL_Rect get_dst();

		// Edit the displayed text
		// \param message The text message 
		void edit_text(const std::string message);

		// Edit the blend transparency
		// \param The alpha value for transparency
		void edit_alpha(uint8_t alpha);

		// Edit the text position
		// \param The `x`, `y` coordinates of the text
		void edit_position(SDL_Point pos);

		// Edit the text position
		// \param The `x`, `y` coordinates of the text
		void edit_position(int x, int y);

		// Edit the color
		// \param color The color
		void edit_color(SDL_Color color);

		/* Edit the position, color, the displayed text and alpha value
		* \param message The text to be displayed
		* \param pos The x, y coordinates of the text
		* \param color The color of the text
		* \param alpha Alpha value for transparency
		*/
		void edit(const std::string message, SDL_Color color, uint8_t alpha = 255, SDL_Point pos = {0,0});

		// Render the text
		void render();

		// Check if the mouse hovered over the asset
		bool mouse_hovered();

		// Check if the mouse left clicked over the asset
		bool mouse_clicked_left();

		// Check if the mouse right clicked over the asset
		bool mouse_clicked_right();

	private:
		std::string m_message;
		SDL_Texture* m_texture;
		SDL_Rect m_dst;
		TTF_Font* m_font;
		SDL_Color m_color;
		uint8_t m_alpha;
	};

	struct rect
	{
		int x, y;
		int w, h;

		rect() = default;
		rect(int x, int y, int w, int h, SDL_Color color = colors::BLACK);

		// Edit the color of the rectangle
		void edit_color(SDL_Color color);

		// Edit the properties of the rectangle
		void edit_properties(int x, int y, int w, int h);

		// Renders rectangle outline to renderer
		void render_outline(uint8_t alpha = 255);

		// Renders rectangle fill to renderer
		void render_fill(uint8_t alpha = 255);

		// Mouse hovered over rectangle
		bool mouse_hovered();

		// Mouse left clicked over rectangle
		bool mouse_clicked_left();

		// Mouse right clicked over rectangle
		bool mouse_clicked_right();

		// Rectangle collided with a type Rect
		bool collided_width(rect rect);

		// Rectangle collided with a type SDL_Rect
		bool collided_with(SDL_Rect rect);

		// Converts type rect to SDL_Rect 
		SDL_Rect c_rec();

	private:
		SDL_Color m_color;
	};

	struct texture
	{
		texture() = default;
		texture(const std::string filepath);
		~texture();

		// Load the texture as a chosen image
		//\param filepath The filepath to the image
		void load(const std::string filepath);

		// Render the texture onto screen with the option to flip it 
		//\param src Properties of the source image
		//\param dst Properties of the image to be rendered on screen
		//\param alpha Alpha value for transparency
		//\param flip Variable that tracks when a flip occurs 
		void render(SDL_Rect& src, SDL_Rect& dst, uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Render the texture onto screen with the option to flip it 
		//\param src Properties of the source image
		//\param dst Properties of the image to be rendered on screen
		//\param alpha Alpha value for transparency
		//\param flip Variable that tracks when a flip occurs 
		void render(rect& src, rect& dst, uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		SDL_Texture* m_sdl_texture = nullptr;
	};

	namespace asset
	{
		// Bckgrounds or overlays that cover the entire screen
		struct background
		{
			background();

			// Load the texture as a chosen image
			//\param filepath The filepath to the image
			void load_texture(const std::string filepath);

			// Render the texture onto screen with the option to flip it 
			//\param alpha Alpha value for transparency
			//\param flip Variable that tracks when a flip occurs 
			void render(uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		private:
			texture m_texture;
			SDL_Rect m_source;
			SDL_Rect m_destination;
		};

		// Any entity or item with a custom size
		struct entity
		{
			// Load the texture as a chosen image
			//\param filepath The filepath to the image
			void load_texture(const std::string filepath);

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
			void set_src(SDL_Rect src);

			// Set the dst values of the image 
			void set_dst(SDL_Rect dst);

			// Set the src values of the image
			void set_src(rect src);

			// Set the dst values of the image 
			void set_dst(rect dst);

			// Get the entity's dst values 
			rect get_dst();

			// Render the entity's texture onto screen with the option to flip it 
			//\param alpha Alpha value for transparency 
			//\param flip Variable that tracks when a flip occurs
			void render(uint8_t alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

			// Check if the mouse hovered over the asset
			bool mouse_hovered();

			// Check if the mouse left clicked over the asset
			bool mouse_clicked_left();

			// Check if the mouse right clicked over the asset
			bool mouse_clicked_right();

			// Rectangle collided with a type Rect
			bool collided_with(entity& entity);

			// Rectangle collided with a type Rect
			bool collided_with(rect rect);

			// Rectangle collided with a type SDL_Rect
			bool collided_with(SDL_Rect rect);

		private:
			texture m_texture;
			SDL_Rect m_source;
			SDL_Rect m_destination;
		};
	};

	namespace render
	{
		// Clear garbage left behind from the renderer
		void clear();

		// Display everything from the renderer to the screen
		void present();

		// Render a color to the renderer
		void color(const SDL_Color color);
	};

	namespace mouse
	{
		// Check if the mouse hovered over any rectangle
		bool hovered(SDL_Rect& rect);

		// Check if the mouse left clicked on any rectangle 
		bool clicked_left(SDL_Rect& rect);

		// Check if the mouse right clicked on any rectangle 
		bool clicked_right(SDL_Rect& rect);


		// Check if the mouse hovered over any rectangle
		bool hovered(rect& rect);

		// Check if the mouse left clicked on any rectangle 
		bool clicked_left(rect& rect);

		// Check if the mouse right clicked on any rectangle 
		bool clicked_right(rect& rect);
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
		struct sound
		{
			bool is_paused = false; // Check if sound is paused or not

			sound() = default;
			sound(const std::string filepath);
			~sound();

			// Load the sound
			void load_sound(const std::string filepath);

			// Get filepath
			std::string get_filepath();

			// Change channel (-1 by default)
			// Note that the change only happens the next time you call `sdl::audio::sound::play()`, whatever was being played before this function call will stay in that channel
			void change_channel(int channel);

			// Adjust volume (128 by default)
			void adjust_volume(int volume);

			// Get the channel sound is current being played in
			int get_channel();

			// Get current volume
			int get_volume();

			// Play the sound
			void play(int loops = 0);

			// Stop the sound
			void stop();

			// Pause the sound
			void pause();

			// Resume the sound
			void resume();

		private:
			Mix_Chunk* m_sound;
			int m_channel = -1;
			int m_volume = 128;
			std::string m_filepath;

		};

		struct music
		{
			bool is_paused = false; // Check if music is paused or not

			music() = default;
			music(const std::string filepath);
			~music();

			// Load the music
			void load_music(const std::string filepath);

			// Get filepath
			std::string get_filepath();

			// Play the music if not already playing
			void play(int loops = 0);

			// Adjust volume (128 by default)
			void adjust_volume(int volume);

			// Get current volume
			int get_volume();

			// Check if music is currently on track 
			// Whether it is paused is irrelevant, this solely checks if it is the current track on.
			bool is_on();

			// Stop the music
			void stop();

			// Pause the music
			void pause();

			// Resume the music
			void resume();

		private:
			Mix_Music* m_music;
			int m_volume = 128;
			std::string m_filepath; // for debugging
		};
	}

	// Initialize all the resources for SDL2 API
	void init(const std::string title, int width, int height, Uint32 flags);

	// Destroy and clean up all the resources for SDL2 API
	void cleanup();

	// Call core event handling at the very start of the game loop
	void handle_events();

	// Check collisions between 2 rectangles
	bool check_collisions(SDL_Rect rectA, SDL_Rect rectB);

	// Check collisions between 2 rectangles
	bool check_collisions(rect rectA, rect rectB);

	// Call core update at the very end of the game loop
	void update();
};