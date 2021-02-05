#pragma once

#include <SDL.h>

#include "Common.h"

class GameScreen;

class GameScreenManager
{
    SDL_Renderer* m_renderer;
    GameScreen* m_current_screen;
    
public:
    GameScreenManager(SDL_Renderer* renderer, SCREENS start_screen);
    ~GameScreenManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    void ChangeScreen(SCREENS new_screen);
};
