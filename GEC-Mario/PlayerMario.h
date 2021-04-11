#pragma once

#include <string>

#include "Player.h"

#ifndef _CHARACTER_MARIO_H
#define _CHARACTER_MARIO_H

class PlayerMario : public Player
{
private:
	const SDL_Keycode GetJumpKey() override;
	const SDL_Keycode GetLeftKey() override;
	const SDL_Keycode GetRightKey() override;

public:
	PlayerMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, SoundEffect* jump_sound);
};

#endif