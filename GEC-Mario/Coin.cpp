#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, Vector2D start_position, Vector2D start_force, LevelMap* map) :
    Character(renderer, "Images/Coin.png", COIN_WIDTH, COIN_HEIGHT, start_position, 0.0f, 0.0f, 0, 18, map)
{
    m_velocity = start_force;
    m_sprite->SetAnimation(0, 0, 0.15f, 3);
}

Coin::~Coin()
{
}
