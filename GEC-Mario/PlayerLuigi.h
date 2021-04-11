#pragma once
#include "Character.h"
#include "Player.h"

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

class PlayerLuigi : public Player
{
private:
	const SDL_Keycode GetJumpKey() override;
	const SDL_Keycode GetLeftKey() override;
	const SDL_Keycode GetRightKey() override;

public:
	PlayerLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, SoundEffect* jump_sound);
};

#endif
