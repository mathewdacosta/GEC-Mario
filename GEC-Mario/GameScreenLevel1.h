#pragma once

#include "GameScreen.h"

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

class Texture2D;

class GameScreenLevel1 : public GameScreen
{
private:
    Texture2D* m_background_texture;

    bool SetUpLevel();

public:
    GameScreenLevel1(SDL_Renderer* renderer);
    ~GameScreenLevel1();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif
