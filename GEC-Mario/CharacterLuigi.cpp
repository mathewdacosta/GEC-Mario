#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map)
    : Character(renderer, "Images/Luigi.png", start_position, 60.0f, 16.0f, map)
{
}

void CharacterLuigi::HandleInput(float deltaTime, SDL_Event e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            m_moving_left = true;
            break;
        case SDLK_d:
            m_moving_right = true;
            break;
        case SDLK_w:
            if (m_can_jump)
                Jump();
            break;
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            m_moving_left = false;
            break;
        case SDLK_d:
            m_moving_right = false;
            break;
        }
        break;
    }
}