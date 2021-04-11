#pragma once
#include "GameScreen.h"
#include "TextBox.h"

class GameScreenError : public GameScreen
{
private:
    Font* m_font;
    TextBox* m_line_1;
    TextBox* m_line_2;

public:
    GameScreenError(SDL_Renderer* renderer, AudioManager* audio_manager);
    ~GameScreenError();

    bool Setup() override;
    void Render() override;
};
