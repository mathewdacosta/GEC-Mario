#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, SoundEffect* jump_sound) :
	Player(renderer, "Images/Mario.png", start_position, MARIO_MOVE_SPEED, INITIAL_JUMP_FORCE, 2, 16.0f, map, jump_sound)
{
}

const SDL_Keycode CharacterMario::GetJumpKey()
{
	return SDLK_w;
}

const SDL_Keycode CharacterMario::GetLeftKey()
{
	return SDLK_a;
}

const SDL_Keycode CharacterMario::GetRightKey()
{
	return SDLK_d;
}