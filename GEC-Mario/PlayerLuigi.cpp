#include "PlayerLuigi.h"

PlayerLuigi::PlayerLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, SoundEffect* jump_sound)
    : Player(renderer, "Images/Luigi.png", LUIGI_WIDTH, LUIGI_HEIGHT, start_position, LUIGI_MOVE_SPEED, INITIAL_JUMP_FORCE, 2, 16.0f, map, jump_sound)
{
}

const SDL_Keycode PlayerLuigi::GetJumpKey()
{
    return SDLK_UP;
}

const SDL_Keycode PlayerLuigi::GetLeftKey()
{
    return SDLK_LEFT;
}

const SDL_Keycode PlayerLuigi::GetRightKey()
{
    return SDLK_RIGHT;
}
