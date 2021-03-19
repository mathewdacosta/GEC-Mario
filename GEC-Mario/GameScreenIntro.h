#pragma once
#include <SDL_mixer.h>

#include "GameScreen.h"
#include "AudioManager.h"
#include "Texture2D.h"

#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

class GameScreenIntro : public GameScreen
{
private:
    Texture2D* m_background_texture;

    bool SetUpLevel();

public:
    GameScreenIntro(SDL_Renderer* renderer, AudioManager* audio_manager);
    ~GameScreenIntro();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif

