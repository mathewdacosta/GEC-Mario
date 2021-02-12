#pragma once
#include "Character.h"

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position);

	void HandleInput(float deltaTime, SDL_Event e) override;
};

#endif
