#include "GameScreenError.h"

#include "Font.h"

GameScreenError::GameScreenError(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session) :
    GameScreen(renderer, audio_manager, session)
{
    m_system_err_cursor = nullptr;
    m_font = nullptr;
    m_line_1 = nullptr;
    m_line_2 = nullptr;
}

GameScreenError::~GameScreenError()
{
    SDL_FreeCursor(m_system_err_cursor);
    delete m_font;
    delete m_line_1;
    delete m_line_2;
}

bool GameScreenError::Setup()
{
    m_system_err_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    
    m_font = new Font(m_renderer, "Fonts/Super-Mario-World.ttf", 18);
    if (!m_font->IsLoaded())
    {
        delete m_font;
        m_font = nullptr;
        // Return true despite error, else we'll get stuck in a loop
        return true;
    }
    
    m_line_1 = new TextBox(m_font, "An error occurred", { 256, 180 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);
    m_line_2 = new TextBox(m_font, "Press ESCAPE to exit", { 256, 220 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);

    return true;
}

void GameScreenError::Render()
{
    SDL_SetCursor(m_system_err_cursor);
    
    m_line_1->Draw();
    m_line_2->Draw();
}
