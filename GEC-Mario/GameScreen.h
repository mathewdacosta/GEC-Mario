#pragma once

#include <SDL.h>

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
class GameScreen
{
protected:
	SDL_Renderer* m_renderer;

public:
	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};
#endif
