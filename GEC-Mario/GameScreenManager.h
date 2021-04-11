#pragma once

#include <SDL.h>

#include "Common.h"
#include "AudioManager.h"

class GameScreen;

class GameScreenManager
{
    SDL_Renderer* m_renderer;
    AudioManager* m_audio_manager;
    GameSession* m_session;
    GameScreen* m_current_screen;
    Screen m_next_screen;
    bool m_screen_queued;

public:
    GameScreenManager(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session, Screen start_screen);
    ~GameScreenManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    void ChangeScreen(Screen new_screen);
    void QueueScreen(Screen next_screen);
};
