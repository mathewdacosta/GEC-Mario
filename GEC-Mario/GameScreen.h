#pragma once

#include <SDL.h>

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "AudioManager.h"

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
	AudioManager* m_audio_manager;
	Mix_Music* m_bgm;

	bool SetBGM(std::string path);

public:
	GameScreen(SDL_Renderer* renderer, AudioManager* audio_manager);
	virtual ~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};
#endif
