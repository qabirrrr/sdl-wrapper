#include "../include/SDL++.h"
#include <iostream>
#include <cstring>

// Namespace (Public)
namespace SDL2
{
	SDL_Renderer* renderer;
	bool allTexturesLoaded = true;
	bool windowIsOpen = true;

	bool leftClicked;
	bool rightClicked;
	SDL_Point mousePos;
};

// Namespace (Private)
namespace SDL2
{
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	const Uint8* currentKeystate;
	Uint8 previousKeystate[SDL_NUM_SCANCODES] = { 0 };
};

SDL2::TTF::TTF(std::string message, SDL_Point pos, SDL_Color color, TTF_Font* font, Uint8 alpha)
{
	Create(message, pos, color, font, alpha);
}

SDL2::TTF::~TTF()
{
	if (m_Texture) {
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}

// Original: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void SDL2::TTF::Create(std::string message, SDL_Point pos, SDL_Color color, TTF_Font* font, Uint8 alpha)
{
	m_Message = message;
	m_Font = font;
	m_Color = color;
	m_Alpha = alpha;

	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(font, message.c_str(), color);
	m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	m_Destination.x = pos.x;
	m_Destination.y = pos.y;
	m_Destination.w = text_width;
	m_Destination.h = text_height;
}

void SDL2::TTF::EditText(std::string message)
{
	m_Message = message;

	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(m_Font, message.c_str(), m_Color);
	m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	SDL_SetTextureAlphaMod(m_Texture, m_Alpha);

	m_Destination.w = text_width;
	m_Destination.h = text_height;
}

void SDL2::TTF::EditAlpha(Uint8 alpha)
{
	m_Alpha = alpha;
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void SDL2::TTF::Edit(std::string message, SDL_Point pos, SDL_Color color, Uint8 alpha)
{
	m_Message = message;
	m_Color = color;
	m_Alpha = alpha;

	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}


	int text_width;
	int text_height;
	SDL_Surface* surface;

	surface = TTF_RenderText_Blended(m_Font, message.c_str(), color);
	m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	SDL_SetTextureBlendMode(m_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_Texture, alpha);

	m_Destination.x = pos.x;
	m_Destination.y = pos.y;
	m_Destination.w = text_width;
	m_Destination.h = text_height;
}

void SDL2::TTF::Render()
{
	SDL_RenderCopy(renderer, m_Texture, NULL, &m_Destination);
}

bool SDL2::TTF::MouseHovered()
{
	return Mouse::Hovered(m_Destination);
}

bool SDL2::TTF::MouseClickedLeft()
{
	return Mouse::ClickedLeft(m_Destination);
}

bool SDL2::TTF::MouseClickedRight()
{
	return Mouse::ClickedRight(m_Destination);
}



// Rect struct
SDL2::Rect::Rect(int x, int y, int w, int h, SDL_Color color)
{
	SetProperties(x, y, w, h);
	SetColor(color);
}
void SDL2::Rect::SetColor(SDL_Color color)
{
	m_Color.r = color.r;
	m_Color.g = color.g;
	m_Color.b = color.b;
}

void SDL2::Rect::SetProperties(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


void SDL2::Rect::RenderOutline(Uint8 alpha)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_SetRenderDrawColor(SDL2::renderer, m_Color.r, m_Color.g, m_Color.b, alpha);
	SDL_RenderDrawRect(SDL2::renderer, &rect);
}

void SDL2::Rect::RenderFill(Uint8 alpha)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_SetRenderDrawColor(SDL2::renderer, m_Color.r, m_Color.g, m_Color.b, alpha);
	SDL_RenderFillRect(SDL2::renderer, &rect);
}

bool SDL2::Rect::MouseHovered()
{
	SDL_Rect rect = { x,y,w,h };
	return Mouse::Hovered(rect);
}

bool SDL2::Rect::MouseClickedLeft()
{
	SDL_Rect rect = { x,y,w,h };
	return Mouse::ClickedLeft(rect);
}

bool SDL2::Rect::MouseClickedRight()
{
	SDL_Rect rect = { x,y,w,h };
	return Mouse::ClickedRight(rect);
}


bool SDL2::Rect::CollidedWith(Rect rect)
{
	SDL_Rect rectA = { x, y, w, h };
	SDL_Rect rectB = rect.c_rec();
	return CheckCollisions(rectA, rectB);
}

bool SDL2::Rect::CollidedWith(SDL_Rect rect)
{
	SDL_Rect rectA = { x, y, w, h };
	return CheckCollisions(rectA, rect);
}

SDL_Rect SDL2::Rect::c_rec()
{
	return { x, y, w, h };
}

// Texture class
SDL2::Texture::Texture(std::string filepath)
{
	Load(filepath);
}

SDL2::Texture::~Texture()
{
	SDL_DestroyTexture(m_SDL_Texture);
}

void SDL2::Texture::Load(std::string filepath)
{
	m_SDL_Texture = IMG_LoadTexture(renderer, filepath.c_str());
	if (m_SDL_Texture == nullptr)
	{
		if (allTexturesLoaded)
		{
			std::cout << "Failed to load textures\n";
			allTexturesLoaded = false;
		}
		std::cout << "Error: " << IMG_GetError() << "\n";
	}
	SDL_SetTextureBlendMode(m_SDL_Texture, SDL_BLENDMODE_BLEND);
}

void SDL2::Texture::Render(SDL_Rect& src, SDL_Rect& dst, Uint8 alpha, SDL_RendererFlip flip)
{
	if (flip == SDL_FLIP_NONE)
	{
		SDL_RenderCopy(renderer, m_SDL_Texture, &src, &dst);
		SDL_SetTextureAlphaMod(m_SDL_Texture, alpha);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_SDL_Texture, &src, &dst, 0, NULL, flip);
		SDL_SetTextureAlphaMod(m_SDL_Texture, alpha);
	}
}

void SDL2::Texture::Render(Rect& Source, Rect& Destination, Uint8 alpha, SDL_RendererFlip flip)
{
	SDL_Rect s = Source.c_rec();
	SDL_Rect d = Destination.c_rec();
	if (flip == SDL_FLIP_NONE)
	{
		SDL_RenderCopy(renderer, m_SDL_Texture, &s, &d);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_SDL_Texture, &s, &d, 0, NULL, flip);
	}
}

// Asset namespace
SDL2::Asset::Background::Background()
{
	m_Source = { 0, 0, screenWidth, screenHeight };
	m_Destination = { 0, 0, screenWidth, screenHeight };
}

void SDL2::Asset::Background::LoadTexture(std::string filepath)
{
	m_Texture.Load(filepath);
}

void SDL2::Asset::Background::Render(Uint8 alpha, SDL_RendererFlip flip)
{
	if (flip == SDL_FLIP_NONE)
	{
		m_Texture.Render(m_Source, m_Destination, alpha);
	}
	else
	{
		m_Texture.Render(m_Source, m_Destination, alpha, flip);
	}
}



void SDL2::Asset::Entity::LoadTexture(std::string filepath)
{
	m_Texture.Load(filepath);
}

void SDL2::Asset::Entity::SetSrc(int x, int y, int w, int h)
{
	m_Source.x = x;
	m_Source.y = y;
	m_Source.w = w;
	m_Source.h = h;
}

void SDL2::Asset::Entity::SetDst(int x, int y, int w, int h)
{
	m_Destination.x = x;
	m_Destination.y = y;
	m_Destination.w = w;
	m_Destination.h = h;
}

void SDL2::Asset::Entity::SetSrc(SDL_Rect src)
{
	m_Source.x = src.x;
	m_Source.y = src.y;
	m_Source.w = src.w;
	m_Source.h = src.h;
}

void SDL2::Asset::Entity::SetDst(SDL_Rect dst)
{
	m_Destination.x = dst.x;
	m_Destination.y = dst.y;
	m_Destination.w = dst.w;
	m_Destination.h = dst.h;
}

SDL_Rect SDL2::Asset::Entity::Dst()
{
	return m_Destination;
}

SDL2::Rect SDL2::Asset::Entity::DstEx()
{
	Rect dst;
	dst.w = m_Destination.w;
	dst.h = m_Destination.h;
	dst.x = m_Destination.x;
	dst.y = m_Destination.y;
	return dst;
}

void SDL2::Asset::Entity::Render(Uint8 alpha, SDL_RendererFlip flip)
{
	if (flip == SDL_FLIP_NONE)
	{
		m_Texture.Render(m_Source, m_Destination, alpha);
	}
	else
	{
		m_Texture.Render(m_Source, m_Destination, alpha, flip);
	}
}

bool SDL2::Asset::Entity::MouseHovered()
{
	return Mouse::Hovered(m_Destination);
}

bool SDL2::Asset::Entity::MouseClickedLeft()
{
	return Mouse::ClickedLeft(m_Destination);
}

bool SDL2::Asset::Entity::MouseClickedRight()
{
	return Mouse::ClickedRight(m_Destination);
}

bool SDL2::Asset::Entity::CollidedWith(Entity& entity)
{
	return CheckCollisions(m_Destination, entity.Dst());
}


bool SDL2::Asset::Entity::CollidedWith(Rect rect)
{
	return rect.CollidedWith(m_Destination);
}

bool SDL2::Asset::Entity::CollidedWith(SDL_Rect rect)
{
	return CheckCollisions(m_Destination, rect);
}



// Render namespace
void SDL2::Render::Clear()
{
	SDL_RenderClear(renderer);
}

void SDL2::Render::Present()
{
	SDL_RenderPresent(renderer);
}

void SDL2::Render::Color(const SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}




// Mouse namespace
bool SDL2::Mouse::Hovered(SDL_Rect& rect)
{
	return SDL_PointInRect(&mousePos, &rect);
}

bool SDL2::Mouse::ClickedLeft(SDL_Rect& rect)
{
	return SDL_PointInRect(&mousePos, &rect) && leftClicked;
}

bool SDL2::Mouse::ClickedRight(SDL_Rect& rect)
{
	return SDL_PointInRect(&mousePos, &rect) && rightClicked;
}


bool SDL2::Mouse::Hovered(Rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mousePos, &r);
}

bool SDL2::Mouse::ClickedLeft(Rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mousePos, &r) && leftClicked;
}

bool SDL2::Mouse::ClickedRight(Rect& rect)
{
	SDL_Rect r = rect.c_rec();
	return SDL_PointInRect(&mousePos, &r) && rightClicked;
}



// Namespace for keystate
void CopyKey(Uint8* dst, const Uint8* src) // helper
{
	std::memcpy(dst, src, SDL_NUM_SCANCODES * sizeof(Uint8));
}

void SDL2::Keys::Update()
{
	CopyKey(previousKeystate, currentKeystate); // previousState = currentState;  (essentially)
}

bool SDL2::Keys::Pressed(SDL_Scancode key)
{
	return currentKeystate[key] && !previousKeystate[key];
}

bool SDL2::Keys::Released(SDL_Scancode key)
{
	return !currentKeystate[key] && previousKeystate[key];
}


bool SDL2::Keys::Held(SDL_Scancode key)
{
	return currentKeystate[key];
}




// Core
void SDL2::Init(std::string title, int width, int height, Uint32 flags)
{
	bool canInit = true;
	screenWidth = width;
	screenHeight = height;

	currentKeystate = SDL_GetKeyboardState(NULL);

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
		std::cout << "Error (TTF): " << SDL_GetError() << "\n";
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

void SDL2::Destroy()
{
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void SDL2::PollEvents()
{
	SDL_Event ev;
	leftClicked = false;
	rightClicked = false;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			windowIsOpen = false;
			break;
		}
		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				leftClicked = true;
			}
			if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				rightClicked = true;
			}
		}
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
	}

}

// Original: https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
bool SDL2::CheckCollisions(SDL_Rect rectA, SDL_Rect rectB)
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

bool SDL2::CheckCollisions(Rect rectA, Rect rectB)
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

void SDL2::Update()
{
	Keys::Update();
	SDL_Delay(1000 / 60);
}