#include "GameScreenGameOver.h"
#include <iomanip>
#include <sstream>

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session) :
    GameScreen(renderer, audio_manager, session)
{
}

GameScreenGameOver::~GameScreenGameOver()
{
    delete m_text_game_over;
    delete m_text_score;
    delete m_text_exit;
    delete m_font;
}

bool GameScreenGameOver::Setup()
{
    m_font = new Font(m_renderer, "Fonts/Super-Mario-World.ttf", 18);
    if (!m_font->IsLoaded())
    {
        delete m_font;
        m_font = nullptr;
        return false;
    }

    std::stringstream scoreText;
    scoreText << "Final Score   " << std::setw(8) << std::setfill('0') << m_session->score;
    
    m_text_game_over = new TextBox(m_font, "..............   GAME OVER   ..............", { 256, 110 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);
    m_text_score = new TextBox(m_font, scoreText.str(), { 256, 180 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);
    m_text_exit = new TextBox(m_font, "Press ESCAPE to exit", { 256, 270 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);

    return true;
}

void GameScreenGameOver::Render()
{
    m_text_game_over->Draw();
    m_text_score->Draw();
    m_text_exit->Draw();
}
