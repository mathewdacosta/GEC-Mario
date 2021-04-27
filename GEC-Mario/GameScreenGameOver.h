#pragma once
#include "Font.h"
#include "GameScreen.h"
#include "TextBox.h"

class GameScreenGameOver : public GameScreen
{
private:
    Font* m_font;
    TextBox* m_text_game_over;
    TextBox* m_text_score;
    TextBox* m_text_exit;

public:
    GameScreenGameOver(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session);
    ~GameScreenGameOver() override;
    bool Setup() override;
    void Render() override;
};
