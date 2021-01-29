#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"
#include "Common.h"
#include "Texture2D.h"


// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;


// Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void Render();


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
	g_texture = new Texture2D(g_renderer);

	if (!g_texture->LoadFromFile("Images/test.bmp"))
	{
		return false;
	}

	return true;
}

void CloseSDL()
{
	// Clear texture
	delete g_texture;
	g_texture = nullptr;
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
		}
	}

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	// Draw texture at location
	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	// Update screen
	SDL_RenderPresent(g_renderer);
}
