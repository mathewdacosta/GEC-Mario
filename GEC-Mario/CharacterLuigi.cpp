#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map)
    : Player(renderer, "Images/Luigi.png", start_position, LUIGI_MOVE_SPEED, INITIAL_JUMP_FORCE, 2, 16.0f, map)
{
}

const SDL_Keycode CharacterLuigi::GetJumpKey()
{
    return SDLK_UP;
}

const SDL_Keycode CharacterLuigi::GetLeftKey()
{
    return SDLK_LEFT;
}

const SDL_Keycode CharacterLuigi::GetRightKey()
{
    return SDLK_RIGHT;
}
