#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

namespace SDL2
{
	extern SDL_Renderer* renderer;
	extern bool allTexturesLoaded;
	extern bool windowIsOpen;

	extern bool leftClicked;
	extern bool rightClicked;
	extern SDL_Point mousePos;

	// Namespace for colors
	namespace Colors
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
	};

	// Class for text
	class TTF
	{
	public:
		TTF() = default;
		TTF(std::string message, SDL_Point pos, SDL_Color color, TTF_Font* font, Uint8 alpha = 255);
		~TTF();

		/* This function creates a piece of text
		*
		* \param Message: The text to be displayed
		* \param Pos: The x, y coordinates of the text
		* \param Color: The color of the text
		* \param Font: The font (to be initialized manually)
		* \param Alpha: Alpha for blend transparency
		*/
		void Create(std::string message, SDL_Point pos, SDL_Color color, TTF_Font* font, Uint8 alpha = 255);

		// This function edits the displayed text.
		// \param The text message 
		void EditText(std::string message);

		// This function edits the blend transparency.
		// \param The text message 
		void EditAlpha(Uint8 alpha);

		/* This function edits either the position, color or the displayed text itself or all.
		* \param Message : The text to be displayed
		* \param Pos : The x, y coordinates of the text
		* \param Color : The color of the text
		* \param Font : The font(to be initialized manually)
		*/
		void Edit(std::string message, SDL_Point pos, SDL_Color color, Uint8 alpha = 255);

		// This function renders the text on screen
		void Render();

		// This method checks if the mouse hovered over the asset
		bool MouseHovered();

		// This method checks if the mouse left clicked over the asset
		bool MouseClickedLeft();

		// This method checks if the mouse right clicked over the asset
		bool MouseClickedRight();

	private:
		std::string m_Message;
		SDL_Texture* m_Texture;
		SDL_Rect m_Destination;
		TTF_Font* m_Font;
		SDL_Color m_Color;
		Uint8 m_Alpha;
	};

	// Struct for rectangles
	struct Rect
	{
		int x, y;
		int w, h;

		Rect() = default;
		Rect(int x, int y, int w, int h, SDL_Color color = Colors::BLACK);

		// Set the color of the rectangle
		void SetColor(SDL_Color color);

		// Set the properties of the rectangle
		void SetProperties(int x, int y, int w, int h);

		// Renders rectangle outline to renderer
		void RenderOutline(Uint8 alpha = 255);

		// Renders rectangle fill to renderer
		void RenderFill(Uint8 alpha = 255);

		// Mouse hovered over rectangle
		bool MouseHovered();

		// Mouse left clicked over rectangle
		bool MouseClickedLeft();

		// Mouse right clicked over rectangle
		bool MouseClickedRight();

		// Rectangle collided with a type Rect
		bool CollidedWith(Rect rect);

		// Rectangle collided with a type SDL_Rect
		bool CollidedWith(SDL_Rect rect);

		// Converts type Rect to SDL_Rect 
		SDL_Rect c_rec();

	private:
		SDL_Color m_Color;
	};

	// Struct for texture. Not intended for use. 
	// Create an Asset, then render with Render method()
	struct Texture
	{
		Texture() = default;
		Texture(std::string filepath);
		~Texture();

		// This method loads the texture as a chosen image
		//\param Filepath: The filepath to the image
		void Load(std::string filepath);

		// This method renders the texture onto screen with the option to flip it 
		//\param Source: Properties of the source image
		//\param Destination: Properties of the image to be rendered on screen
		//\param Flip: Variable that tracks when a flip occurs 
		void Render(SDL_Rect& src, SDL_Rect& dst, Uint8 alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// This method renders the texture onto screen with the option to flip it 
		//\param Source: Properties of the source image
		//\param Destination: Properties of the image to be rendered on screen
		//\param Flip: Variable that tracks when a flip occurs 
		void Render(Rect& src, Rect& dst, Uint8 alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		SDL_Texture* m_SDL_Texture = nullptr;
	};

	// An asset for future renders
	// For textures that cover the entire screen:
	// * Background 
	// For custom sized textures:
	// * Entity
	namespace Asset
	{
		// This can be used for backgrounds or overlays
		struct Background
		{
			Background();

			// This method loads the texture as a chosen image
			//\param The filepath to the image
			void LoadTexture(std::string filepath);

			// This method renders the texture onto screen with the option to flip it 
			//\param Flip: Variable that tracks when a flip occurs 
			void Render(Uint8 alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

		private:
			Texture m_Texture;
			SDL_Rect m_Source;
			SDL_Rect m_Destination;
		};

		// This can be used for any entity or item
		struct Entity
		{
			// This method loads the texture as a chosen image
			//\param The filepath to the image
			void LoadTexture(std::string filepath);

			// This method sets the src values of the image
			//\param x: The x coordinate of the image source
			//\param y: The y coordinate of the image source
			//\param w: The width of the image source
			//\param h: The height of the image source
			void SetSrc(int x, int y, int w, int h);

			// This method sets the dst values of the image 
			//\param x: The x coordinate of the image destination
			//\param y: The y coordinate of the image destination
			//\param w: The width of the image destination
			//\param h: The height of the image destination
			void SetDst(int x, int y, int w, int h);

			// This method sets the src values of the image
			void SetSrc(SDL_Rect src);

			// This method sets the dst values of the image 
			void SetDst(SDL_Rect dst);

			// This method returns the entity's dst values (SDL_Rect type)
			SDL_Rect Dst();

			// This method returns the entity's dst values (Rect type)
			Rect DstEx();

			// This method renders the entity's texture onto screen with the option to flip it 
			//\param Flip: Variable that tracks when a flip occurs 
			void Render(Uint8 alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

			// This method checks if the mouse hovered over the asset
			bool MouseHovered();

			// This method checks if the mouse left clicked over the asset
			bool MouseClickedLeft();

			// This method checks if the mouse right clicked over the asset
			bool MouseClickedRight();

			// Rectangle collided with a type Rect
			bool CollidedWith(Entity& entity);

			// Rectangle collided with a type Rect
			bool CollidedWith(Rect rect);

			// Rectangle collided with a type SDL_Rect
			bool CollidedWith(SDL_Rect rect);

		private:
			Texture m_Texture;
			SDL_Rect m_Source;
			SDL_Rect m_Destination;
		};
	};

	// Render methods
	namespace Render
	{
		// This method clears garbage left behind from the renderer
		void Clear();

		// This method presents everything from the renderer to the screen
		void Present();

		// This method renders a color to the renderer
		void Color(const SDL_Color color);
	};

	// This namespace tracks the mouse
	namespace Mouse
	{
		// This method checks if the mouse hovered over any rectangle
		bool Hovered(SDL_Rect& rect);

		// This method checks if the mouse left clicked on any rectangle 
		bool ClickedLeft(SDL_Rect& rect);

		// This method checks if the mouse right clicked on any rectangle 
		bool ClickedRight(SDL_Rect& rect);


		// This method checks if the mouse hovered over any rectangle
		bool Hovered(Rect& rect);

		// This method checks if the mouse left clicked on any rectangle 
		bool ClickedLeft(Rect& rect);

		// This method checks if the mouse right clicked on any rectangle 
		bool ClickedRight(Rect& rect);
	};

	namespace Keys
	{
		// Call update at the very end of game loop (if core update wasn't called, otherwise it would be redundant)
		void Update();

		// Check if key is pressed
		bool Pressed(SDL_Scancode key);

		// Check if key is released
		bool Released(SDL_Scancode key);

		// Check if key is being held
		bool Held(SDL_Scancode key);
	};

	/* This method initializes all the resources for SDL2 API
	*
	* \param Window title, dimensions and flags
	*/
	void Init(std::string title, int width, int height, Uint32 flags);

	// This destroys and cleans up all the resources for SDL2 API.
	void Destroy();

	// Call core event handling at the very start of the game loop
	void PollEvents();

	// Check collisions between 2 rectangles
	bool CheckCollisions(SDL_Rect rectA, SDL_Rect rectB);

	// Check collisions between 2 rectangles
	bool CheckCollisions(Rect rectA, Rect rectB);

	// Call core update at the very end of the game loop
	void Update();
};