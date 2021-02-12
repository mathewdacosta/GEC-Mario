#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, Vector2D start_position)
	: Character(renderer, "Images/Mario.png", start_position, 50.0f, 16.0f)
{
}

void CharacterMario::HandleInput(float deltaTime, SDL_Event e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            m_moving_left = true;
            break;
        case SDLK_RIGHT:
            m_moving_right = true;
            break;
        case SDLK_UP:
            if (m_can_jump)
                Jump();
            break;
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            m_moving_left = false;
            break;
        case SDLK_RIGHT:
            m_moving_right = false;
            break;
        }
        break;
    }
}