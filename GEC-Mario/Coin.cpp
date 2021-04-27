#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, Vector2D start_position, Vector2D start_force, LevelMap* map) :
    Character(renderer, "Images/Coin.png", COIN_WIDTH, COIN_HEIGHT, start_position, 0.0f, 0.0f, 0, 18, map),
    m_lifetime(0.0f)
{
    m_velocity = start_force;
    m_sprite->SetAnimation(0, 0, 0.15f, 3);
}

Coin::~Coin()
{
}


void Coin::Update(float deltaTime, SDL_Event e)
{
    Character::Update(deltaTime, e);

    m_lifetime += deltaTime;
}


void Coin::Render()
{
    if (m_alive)
    {
        Character::Render();
    }
}

float Coin::GetLifetime() const
{
    return m_lifetime;
}
