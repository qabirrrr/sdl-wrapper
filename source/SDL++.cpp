#include "../include/SDL++.h"
#include <iostream>
#include <cstring>

// Namespace (Public)
namespace sdl
{
	SDL_Renderer* renderer;
	bool all_textures_loaded = true;
	bool running = true;

	bool left_clicked;
	bool right_clicked;
	SDL_Point mouse_pos;
};

// Namespace (Private)
namespace sdl
{
	SDL_Window* window;
	int screen_width;
	int screen_height;
	Mix_Music* current_music;
	const uint8_t* current_keystate;
	uint8_t previous_keystate[SDL_NUM_SCANCODES] = { 0 };
};



// Namespace for colors
std::vector<SDL_Color> sdl::colors::get_primary()
{
	std::vector<SDL_Color> colors =
	{
		colors::RED,
		colors::YELLOW,
		colors::BLUE
	};
	return colors;
}


std::vector<SDL_Color> sdl::colors::get_secondary()
{
	std::vector<SDL_Color> colors =
	{
		colors::ORANGE,
		colors::GREEN,
		colors::PURPLE,
	};
	return colors;
}

std::vector<SDL_Color> sdl::colors::get_foundational()
{
	std::vector<SDL_Color> colors =
	{
		colors::ORANGE,
		colors::RED,
		colors::GREEN,
		colors::YELLOW,
		colors::PURPLE,
		colors::BLUE
	};
	return colors;
}

std::vector<SDL_Color> sdl::colors::get_all()
{
	std::vector<SDL_Color> colors =
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
	return colors;
}



// Namespace for ttf
sdl::ttf::ttf(const std::string message, SDL_Color color, TTF_Font* font, uint8_t alpha, SDL_Point pos)
{
	create(message, color, font, alpha, pos);
}

sdl::ttf::~ttf()
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

// Original: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void sdl::ttf::create(const std::string message, SDL_Color color, TTF_Font* font, uint8_t alpha, SDL_Point pos)
{
	m_message = message;
	m_font = font;
	m_color = color;
	m_alpha = alpha;

	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(font, message.c_str(), color);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	m_dst.x = pos.x;
	m_dst.y = pos.y;
	m_dst.w = text_width;
	m_dst.h = text_height;
}

SDL_Rect sdl::ttf::get_dst()
{
	return m_dst;
}

void sdl::ttf::edit_text(const std::string message)
{
	m_message = message;

	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}

	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(m_font, message.c_str(), m_color);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	SDL_SetTextureAlphaMod(m_texture, m_alpha);

	m_dst.w = text_width;
	m_dst.h = text_height;
}

void sdl::ttf::edit_alpha(uint8_t alpha)
{
	m_alpha = alpha;
	SDL_SetTextureAlphaMod(m_texture, alpha);
}

void sdl::ttf::edit_position(SDL_Point pos)
{
	m_dst.x = pos.x;
	m_dst.y = pos.y;
}

void sdl::ttf::edit_position(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

void sdl::ttf::edit_color(SDL_Color color)
{
	m_color = color;
}

void sdl::ttf::edit(const std::string message, SDL_Color color, uint8_t alpha, SDL_Point pos)
{
	m_message = message;
	m_color = color;
	m_alpha = alpha;

	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}


	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(m_font, message.c_str(), color);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_texture, alpha);

	m_dst.x = pos.x;
	m_dst.y = pos.y;
	m_dst.w = text_width;
	m_dst.h = text_height;
}

void sdl::ttf::render()
{
	SDL_RenderCopy(renderer, m_texture, NULL, &m_dst);
}

bool sdl::ttf::mouse_hovered()
{
	return mouse::hovered(m_dst);
}

bool sdl::ttf::mouse_clicked_left()
{
	return mouse::clicked_left(m_dst);
}

bool sdl::ttf::mouse_clicked_right()
{
	return mouse::clicked_right(m_dst);
}



// Rect struct
sdl::rect::rect(int x, int y, int w, int h, SDL_Color color)
{
	edit_properties(x, y, w, h);
	edit_color(color);
}
void sdl::rect::edit_color(SDL_Color color)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;
}

void sdl::rect::edit_properties(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


void sdl::rect::render_outline(uint8_t alpha)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_SetRenderDrawColor(sdl::renderer, m_color.r, m_color.g, m_color.b, alpha);
	SDL_RenderDrawRect(sdl::renderer, &rect);
}

void sdl::rect::render_fill(uint8_t alpha)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_SetRenderDrawColor(sdl::renderer, m_color.r, m_color.g, m_color.b, alpha);
	SDL_RenderFillRect(sdl::renderer, &rect);
}

bool sdl::rect::mouse_hovered()
{
	SDL_Rect rect = { x,y,w,h };
	return mouse::hovered(rect);
}

bool sdl::rect::mouse_clicked_left()
{
	SDL_Rect rect = { x,y,w,h };
	return mouse::clicked_left(rect);
}

bool sdl::rect::mouse_clicked_right()
{
	SDL_Rect rect = { x,y,w,h };
	return mouse::clicked_right(rect);
}


bool sdl::rect::collided_width(rect rect)
{
	SDL_Rect rectA = { x, y, w, h };
	SDL_Rect rectB = rect.c_rec();
	return check_collisions(rectA, rectB);
}

bool sdl::rect::collided_with(SDL_Rect rect)
{
	SDL_Rect rectA = { x, y, w, h };
	return check_collisions(rectA, rect);
}

SDL_Rect sdl::rect::c_rec()
{
	return { x, y, w, h };
}

// Texture class
sdl::texture::texture(const std::string filepath)
{
	load(filepath);
}

sdl::texture::~texture()
{
	SDL_DestroyTexture(m_sdl_texture);
}

void sdl::texture::load(const std::string filepath)
{
	m_sdl_texture = IMG_LoadTexture(renderer, filepath.c_str());
	if (m_sdl_texture == nullptr)
	{
		if (all_textures_loaded)
		{
			std::cout << "Failed to load textures\n";
			all_textures_loaded = false;
		}
		std::cout << "Error: " << IMG_GetError() << "\n";
	}
	SDL_SetTextureBlendMode(m_sdl_texture, SDL_BLENDMODE_BLEND);
}

void sdl::texture::render(SDL_Rect& src, SDL_Rect& dst, uint8_t alpha, SDL_RendererFlip flip)
{
	if (flip == SDL_FLIP_NONE)
	{
		SDL_RenderCopy(renderer, m_sdl_texture, &src, &dst);
		SDL_SetTextureAlphaMod(m_sdl_texture, alpha);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_sdl_texture, &src, &dst, 0, NULL, flip);
		SDL_SetTextureAlphaMod(m_sdl_texture, alpha);
	}
}

void sdl::texture::render(rect& src, rect& dst, uint8_t alpha, SDL_RendererFlip flip)
{
	SDL_Rect s = src.c_rec();
	SDL_Rect d = dst.c_rec();
	if (flip == SDL_FLIP_NONE)
	{
		SDL_RenderCopy(renderer, m_sdl_texture, &s, &d);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_sdl_texture, &s, &d, 0, NULL, flip);
	}
}

// Asset namespace
sdl::asset::background::background()
{
	m_source = { 0, 0, screen_width, screen_height };
	m_destination = { 0, 0, screen_width, screen_height };
}

void sdl::asset::background::load_texture(const std::string filepath)
{
	m_texture.load(filepath);
}

void sdl::asset::background::render(uint8_t alpha, SDL_RendererFlip flip)
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



void sdl::asset::entity::load_texture(const std::string filepath)
{
	m_texture.load(filepath);
}

void sdl::asset::entity::set_src(int x, int y, int w, int h)
{
	m_source.x = x;
	m_source.y = y;
	m_source.w = w;
	m_source.h = h;
}

void sdl::asset::entity::set_dst(int x, int y, int w, int h)
{
	m_destination.x = x;
	m_destination.y = y;
	m_destination.w = w;
	m_destination.h = h;
}

void sdl::asset::entity::set_src(SDL_Rect src)
{
	m_source.x = src.x;
	m_source.y = src.y;
	m_source.w = src.w;
	m_source.h = src.h;
}

void sdl::asset::entity::set_dst(SDL_Rect dst)
{
	m_destination.x = dst.x;
	m_destination.y = dst.y;
	m_destination.w = dst.w;
	m_destination.h = dst.h;
}

void sdl::asset::entity::set_src(rect src)
{
	m_source.x = src.x;
	m_source.y = src.y;
	m_source.w = src.w;
	m_source.h = src.h;
}

void sdl::asset::entity::set_dst(rect dst)
{
	m_destination.x = dst.x;
	m_destination.y = dst.y;
	m_destination.w = dst.w;
	m_destination.h = dst.h;
}

sdl::rect sdl::asset::entity::get_dst()
{
	rect dst;
	dst.w = m_destination.w;
	dst.h = m_destination.h;
	dst.x = m_destination.x;
	dst.y = m_destination.y;
	return dst;
}

void sdl::asset::entity::render(uint8_t alpha, SDL_RendererFlip flip)
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

bool sdl::asset::entity::mouse_hovered()
{
	return mouse::hovered(m_destination);
}

bool sdl::asset::entity::mouse_clicked_left()
{
	return mouse::clicked_left(m_destination);
}

bool sdl::asset::entity::mouse_clicked_right()
{
	return mouse::clicked_right(m_destination);
}

bool sdl::asset::entity::collided_with(entity& entity)
{
	return check_collisions(m_destination, (entity.get_dst()).c_rec());
}


bool sdl::asset::entity::collided_with(rect rect)
{
	return rect.collided_with(m_destination);
}

bool sdl::asset::entity::collided_with(SDL_Rect rect)
{
	return check_collisions(m_destination, rect);
}



// Render namespace
void sdl::render::clear()
{
	SDL_RenderClear(renderer);
}

void sdl::render::present()
{
	SDL_RenderPresent(renderer);
}

void sdl::render::color(const SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}




// Mouse namespace
bool sdl::mouse::hovered(SDL_Rect& rect)
{
	return SDL_PointInRect(&mouse_pos, &rect);
}

bool sdl::mouse::clicked_left(SDL_Rect& rect)
{
	return SDL_PointInRect(&mouse_pos, &rect) && left_clicked;
}

bool sdl::mouse::clicked_right(SDL_Rect& rect)
{
	return SDL_PointInRect(&mouse_pos, &rect) && right_clicked;
}


bool sdl::mouse::hovered(rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mouse_pos, &r);
}

bool sdl::mouse::clicked_left(rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mouse_pos, &r) && left_clicked;
}

bool sdl::mouse::clicked_right(rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mouse_pos, &r) && right_clicked;
}



// Namespace for keystate
void copy_key(uint8_t* dst, const uint8_t* src) // helper
{
	std::memcpy(dst, src, SDL_NUM_SCANCODES * sizeof(uint8_t));
}

void sdl::keys::update()
{
	copy_key(previous_keystate, current_keystate); // previousState = currentState;  (essentially)
}

bool sdl::keys::pressed(SDL_Scancode key)
{
	return current_keystate[key] && !previous_keystate[key];
}

bool sdl::keys::released(SDL_Scancode key)
{
	return !current_keystate[key] && previous_keystate[key];
}


bool sdl::keys::held(SDL_Scancode key)
{
	return current_keystate[key];
}



// Namespace for audio
sdl::audio::sound::sound(const std::string filepath)
{
	load_sound(filepath);
}

sdl::audio::sound::~sound()
{
	Mix_FreeChunk(m_sound);
}

void sdl::audio::sound::load_sound(const std::string filepath)
{
	m_filepath = filepath;
	m_sound = Mix_LoadWAV(m_filepath.c_str());
	if (m_sound == nullptr)
	{
		std::cout << "Error (Loading sound): " << Mix_GetError() << '\n';
	}
}

std::string sdl::audio::sound::get_filepath()
{
	return m_filepath;
}

void sdl::audio::sound::change_channel(int channel)
{
	m_channel = channel;
}

void sdl::audio::sound::adjust_volume(int volume)
{
	m_volume = volume;
	Mix_VolumeChunk(m_sound, volume);
}

int sdl::audio::sound::get_channel()
{
	return m_channel;
}

int sdl::audio::sound::get_volume()
{
	return m_volume;
}

void sdl::audio::sound::play(int loops)
{
	Mix_PlayChannel(m_channel, m_sound, loops); 
}

void sdl::audio::sound::stop()
{
	Mix_HaltChannel(m_channel);
}

void sdl::audio::sound::pause()
{
	Mix_Pause(m_channel);
	is_paused = true;
}

void sdl::audio::sound::resume()
{
	Mix_Resume(m_channel);
	is_paused = false;
}


sdl::audio::music::music(const std::string filepath)
{
	load_music(filepath);
}

void sdl::audio::music::load_music(const std::string filepath)
{
	m_filepath = filepath;
	m_music = Mix_LoadMUS(m_filepath.c_str());
	if (m_music == nullptr)
	{
		std::cout << "Error (Loading music): " << Mix_GetError() << '\n';
	}
}

std::string sdl::audio::music::get_filepath()
{
	return m_filepath;
}

void sdl::audio::music::adjust_volume(int volume)
{
	m_volume = volume;
	Mix_VolumeMusic(volume);
}

int sdl::audio::music::get_volume()
{
	return m_volume;
}

bool sdl::audio::music::is_on()
{
	if (current_music != m_music || Mix_PlayingMusic() == 0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}


void sdl::audio::music::play(int loops)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, loops);
		current_music = m_music;
	}
}

void sdl::audio::music::stop()
{
	Mix_HaltMusic();
	current_music = nullptr;
}

void sdl::audio::music::pause()
{
	Mix_PauseMusic();
	is_paused = true;
}

void sdl::audio::music::resume()
{
	Mix_ResumeMusic();
	is_paused = false;
}


sdl::audio::music::~music()
{
	Mix_FreeMusic(m_music);
}


// Core
void sdl::init(const std::string title, int width, int height, Uint32 flags)
{
	bool canInit = true;
	screen_width = width;
	screen_height = height;

	current_keystate = SDL_GetKeyboardState(NULL);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		if (canInit)
		{
			std::cout << "API failed to load\n";
			canInit = false;
		}
		std::cout << "Error (SDL): " << SDL_GetError() << "\n";
	}

	if (TTF_Init())
	{
		if (canInit)
		{
			std::cout << "API failed to load\n";
			canInit = false;
		}
		std::cout << "Error (TTF): " << SDL_GetError() << "\n";
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		if (canInit)
		{
			std::cout << "API failed to load\n";
			canInit = false;
		}
		std::cout << "Error (Mixer): " << SDL_GetError() << "\n";
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window == nullptr)
	{
		if (canInit)
		{
			std::cout << "API failed to load\n";
			canInit = false;
		}
		std::cout << "Error (Window): " << SDL_GetError() << "\n";
	}

	Uint32 rf = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, rf);
	if (renderer == nullptr)
	{
		if (canInit)
		{
			std::cout << "API failed to load\n";
			canInit = false;
		}
		std::cout << "Error (Renderer): " << SDL_GetError() << "\n";
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void sdl::cleanup()
{
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void sdl::handle_events()
{
	SDL_Event ev;
	left_clicked = false;
	right_clicked = false;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			running = false;
			break;
		}
		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				left_clicked = true;
			}
			if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				right_clicked = true;
			}
		}
		SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	}

}

// Original: https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
bool sdl::check_collisions(SDL_Rect rectA, SDL_Rect rectB)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rectA.x;
	rightA = rectA.x + rectA.w;
	topA = rectA.y;
	bottomA = rectA.y + rectA.h;

	//Calculate the sides of rect B
	leftB = rectB.x;
	rightB = rectB.x + rectB.w;
	topB = rectB.y;
	bottomB = rectB.y + rectB.h;

	//If any of the sides from A are outside of B
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

	//If none of the sides from A are outside B
	return true;
}

bool sdl::check_collisions(rect rectA, rect rectB)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rectA.x;
	rightA = rectA.x + rectA.w;
	topA = rectA.y;
	bottomA = rectA.y + rectA.h;

	//Calculate the sides of rect B
	leftB = rectB.x;
	rightB = rectB.x + rectB.w;
	topB = rectB.y;
	bottomB = rectB.y + rectB.h;

	//If any of the sides from A are outside of B
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

	//If none of the sides from A are outside B
	return true;
}

void sdl::update()
{
	keys::update();
	SDL_Delay(1000 / 60);
}