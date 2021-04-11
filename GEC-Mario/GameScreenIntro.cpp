#include "GameScreenIntro.h"

#include <iostream>
#include <sstream>

#include "TextBox.h"

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

    m_text_1p = new TextBox(m_hud_font, "ONE PLAYER", { 256, 220 }, TextColor::WHITE, TextColor::BLACK, false, TextAlignHorizontal::CENTER);
    m_text_2p = new TextBox(m_hud_font, "TWO PLAYERS", { 256, 250 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::CENTER);
    m_text_mouse_pos = new TextBox(m_hud_font, "MOUSE", { 500, 410 }, TextColor::WHITE, TextColor::BLACK, false, TextAlignHorizontal::RIGHT, TextAlignVertical::BOTTOM);
    
    return true;
}

void GameScreenIntro::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

    // Draw text
    m_text_1p->Draw();
    m_text_2p->Draw();
    m_text_mouse_pos->Draw();
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button)
        {
        case SDL_BUTTON_LEFT:
            break;
        }
    }

    SDL_GetMouseState(&m_mouse_x, &m_mouse_y);

    // Cursor position text
    std::stringstream score;
    score << "MOUSE X " << m_mouse_x << " Y " << m_mouse_y;
    m_text_mouse_pos->SetText(score.str());

    // if text boxes are hovered over, draw background
    m_text_1p->SetDrawBg(CheckTextBoxHover(m_text_1p));
    m_text_2p->SetDrawBg(CheckTextBoxHover(m_text_2p));
}


bool GameScreenIntro::CheckTextBoxHover(TextBox* text_box) const
{
    SDL_Rect bounds = text_box->GetBoundingBox();

    return bounds.x < m_mouse_x && bounds.x + bounds.w > m_mouse_x
        && bounds.y < m_mouse_y && bounds.y + bounds.h > m_mouse_y;
}
