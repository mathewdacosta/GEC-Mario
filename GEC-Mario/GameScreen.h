#pragma once

#include <SDL.h>

#include "Common.h"

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "AudioManager.h"

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
	AudioManager* m_audio_manager;
	GameSession* m_session;
	Mix_Music* m_bgm;

	bool SetBGM(std::string path);

public:
	GameScreen(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session);
	virtual ~GameScreen();

	virtual bool Setup() = 0;
	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e);
};
#endif
