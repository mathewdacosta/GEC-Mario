#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "AudioManager.h"
#include "constants.h"
#include "Common.h"
#include "GameScreenManager.h"


// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
AudioManager* g_audio_manager = nullptr;
GameScreenManager* g_screen_manager = nullptr;
GameSession g_session = GameSession();

Uint32 g_old_time;

// Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();


// Function implementations
int main(int argc, char* args[])
{
	if (InitSDL())
	{
		// Set up screen manager
		g_screen_manager = new GameScreenManager(g_renderer, g_audio_manager, &g_session, Screen::INTRO);

		// Set time at start of loop
		g_old_time = SDL_GetTicks();
		
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

	g_audio_manager = new AudioManager();

	if (!(g_audio_manager->Setup()))
	{
		std::cout << "Audio setup failed." << std::endl;
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

	if (TTF_Init() < 0)
	{
		std::cout << "SDL_ttf initialisation failed. Error: " << TTF_GetError();
		return false;
	}

	return true;
}

void CloseSDL()
{
	// Release game screen manager
	delete g_screen_manager;
	g_screen_manager = nullptr;
	
	// Release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	
	// Release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	
	// Shut down audio
	delete g_audio_manager;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	
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
		case SDLK_ESCAPE:
			return true;
		case SDLK_SLASH:
			g_screen_manager->ChangeScreen(Screen::INTRO);
			break;
		case SDLK_COMMA:
			g_screen_manager->ChangeScreen(Screen::LEVEL_1);
			break;
		case SDLK_PERIOD:
			g_screen_manager->ChangeScreen(Screen::LEVEL_2);
			break;
		case SDLK_HASH:
			g_screen_manager->ChangeScreen(Screen::GAME_OVER);
			break;
		case SDLK_QUOTE:
			g_screen_manager->ChangeScreen(Screen::ERROR);
			break;
		}
	}

	g_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x10, 0xFF);
	SDL_RenderClear(g_renderer);

	// Render screen manager
	g_screen_manager->Render();

	// Update screen
	SDL_RenderPresent(g_renderer);
}
