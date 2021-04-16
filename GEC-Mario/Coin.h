#pragma once
#include "Character.h"

class Coin : public Character
{
public:
    Coin(SDL_Renderer* renderer, Vector2D start_position, Vector2D start_force, LevelMap* map);
    ~Coin();
};
