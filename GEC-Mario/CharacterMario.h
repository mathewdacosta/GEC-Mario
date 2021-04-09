#pragma once

#include <string>

#include "Player.h"

#ifndef _CHARACTER_MARIO_H
#define _CHARACTER_MARIO_H

class CharacterMario : public Player
{
private:
	const SDL_Keycode GetJumpKey() override;
	const SDL_Keycode GetLeftKey() override;
	const SDL_Keycode GetRightKey() override;

public:
	CharacterMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map);
};

#endif