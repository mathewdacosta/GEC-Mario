#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

class GameScreenIntro : public GameScreen
{
private:
    Texture2D* m_background_texture;

    bool SetUpLevel();

public:
    GameScreenIntro(SDL_Renderer* renderer);
    ~GameScreenIntro();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif

