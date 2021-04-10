#include "GameScreenIntro.h"

#include <iostream>
#include <sstream>

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, AudioManager* audio_manager) : GameScreen(renderer, audio_manager)
{
}

GameScreenIntro::~GameScreenIntro()
{
    delete m_background_texture;
    delete m_hud_font;
}

bool GameScreenIntro::Setup()
{
    // Load background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/test-2.bmp"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }

    if (!SetBGM("Audio/Music/MarioUnderworld.mp3"))
    {
        // Already logged - just return
        return false;
    }

    m_hud_font = new Font(m_renderer, "Fonts/Super-Mario-World.ttf", 16);
    if (!m_hud_font->IsLoaded())
    {
        // Already logged - just return
        return false;
    }
    
    return true;
}

void GameScreenIntro::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

    // Draw text
    m_hud_font->DrawSolid("1 PLAYER", { 256, 220 }, TextColor::WHITE, TextAlignHorizontal::CENTER);
    m_hud_font->DrawShaded("! 2 players !", { 256, 250 }, TextColor::WHITE, TextColor::BLACK, TextAlignHorizontal::CENTER);
    int x, y = 0;
    SDL_GetMouseState(&x, &y);
    std::stringstream score;
    score << "X " << x << " Y " << y;
    m_hud_font->DrawBlended(score.str(), { 500, 400 }, { 0, 0, 0, 0xFF }, TextAlignHorizontal::RIGHT, TextAlignVertical::BOTTOM);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}
