#pragma once

#include "GameScreen.h"
#include "AudioManager.h"
#include "Font.h"
#include "GameScreenManager.h"
#include "TextBox.h"
#include "Texture2D.h"

#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

class GameScreenIntro : public GameScreen
{
private:
    GameScreenManager* m_screen_manager;
    Texture2D* m_background_texture;
    Font* m_hud_font;
    TextBox* m_text_2p;
    TextBox* m_text_high_scores;
    TextBox* m_text_mouse_pos;
    
    int m_mouse_x;
    int m_mouse_y;

    bool CheckTextBoxHover(TextBox* text_box) const;

public:
    GameScreenIntro(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session);
    ~GameScreenIntro();

	bool Setup() override;

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif

