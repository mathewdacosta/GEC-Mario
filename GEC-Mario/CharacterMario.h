#pragma once

#include <string>

#include "Character.h"

#ifndef _CHARACTER_MARIO_H
#define _CHARACTER_MARIO_H

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map);

	void HandleInput(float deltaTime, SDL_Event e) override;
};

#endif