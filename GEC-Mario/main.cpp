#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"


// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;
SDL_RendererFlip g_flip = SDL_FLIP_NONE;
int g_angle = 0;


// Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(std::string path);
void FreeTexture();


// Function implementations
int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}

		CloseSDL();
	}

	return 0;
}


bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	g_window = SDL_CreateWindow("GEC Mario",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (g_window == nullptr)
	{
		std::cout << "Window creation failed. Error: " << SDL_GetError();
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer == nullptr)
	{
		std::cout << "Renderer initialisation failed. Error: " << SDL_GetError();
		return false;
	}

	int imageFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imageFlags) & imageFlags))
	{
		std::cout << "SDL_Image initialisation failed. Error: " << IMG_GetError();
		return false;
	}

	// Load background texture
	g_texture = LoadTextureFromFile("Images/test.bmp");
	if (g_texture == nullptr)
	{
		return false;
	}

	return true;
}

void CloseSDL()
{
	// Clear texture
	FreeTexture();
	// Release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	// Release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		case SDLK_1:
			g_flip = SDL_FLIP_NONE;
			break;
		case SDLK_2:
			g_flip = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_3:
			g_flip = SDL_FLIP_VERTICAL;
			break;
		case SDLK_4:
			g_flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
			break;
		case SDLK_LEFTBRACKET:
			g_angle -= 1;
			break;
		case SDLK_RIGHTBRACKET:
			g_angle += 1;
			break;
		}
	}

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	// Position of texture
	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// Draw texture at location
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, g_angle, NULL, g_flip);

	// Update screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(std::string path)
{
	// Remove memory used for previous texture
	SDL_Texture* p_texture = nullptr;

	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface == nullptr)
	{
		std::cout << "Could not create surface from file. Error: " << IMG_GetError();
		return nullptr;
	}

	p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
	if (p_texture == nullptr)
	{
		std::cout << "Could not create texture from surface. Error: " << SDL_GetError();
	}
	// Remove loaded surface now we have a texture
	SDL_FreeSurface(p_surface);

	return p_texture;
}

void FreeTexture()
{
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
