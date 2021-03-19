#pragma once

#include <SDL.h>

#include "Common.h"
#include "AudioManager.h"

class GameScreen;

class GameScreenManager
{
    SDL_Renderer* m_renderer;
    AudioManager* m_audio_manager;
    GameScreen* m_current_screen;
    
public:
    GameScreenManager(SDL_Renderer* renderer, AudioManager* audio_manager, SCREENS start_screen);
    ~GameScreenManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    void ChangeScreen(SCREENS new_screen);
};
