#include "../../include/SDL++"
#include "../../include/globals"
#include <iostream>

namespace sdl
{
	bool init(const std::string& title, int width, int height, Uint32 flags)
	{
		bool can_init = true;
		g_width = width;
		g_height = height;

		g_current_keystate = SDL_GetKeyboardState(NULL);

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			if (can_init)
			{
				std::cout << "API failed to load\n";
				can_init = false;
			}
			std::cout << "Error (SDL): " << SDL_GetError() << '\n';
		}

		if (TTF_Init())
		{
			if (can_init)
			{
				std::cout << "API failed to load\n";
				can_init = false;
			}
			std::cout << "Error (TTF): " << SDL_GetError() << '\n';
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			if (can_init)
			{
				std::cout << "API failed to load\n";
				can_init = false;
			}
			std::cout << "Error (Mixer): " << SDL_GetError() << '\n';
		}

		g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (g_window == nullptr)
		{
			if (can_init)
			{
				std::cout << "API failed to load\n";
				can_init = false;
			}
			std::cout << "Error (Window): " << SDL_GetError() << '\n';
		}

		Uint32 rf = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
		g_renderer = SDL_CreateRenderer(g_window, -1, rf);
		if (g_renderer == nullptr)
		{
			if (can_init)
			{
				std::cout << "API failed to load\n";
				can_init = false;
			}
			std::cout << "Error (Renderer): " << SDL_GetError() << '\n';
		}

		SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

		SDL_StartTextInput();

		return can_init;
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

	bool check_collisions(const SDL_Rect& rectA, const SDL_Rect& rectB) // https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
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
		SDL_Delay(1000/60);
	}

	SDL_Renderer* get_renderer()
	{
		return g_renderer;
	}

};






