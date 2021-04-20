#include "Enemy.h"
#include "Texture2D.h"


Enemy::Enemy(SDL_Renderer* renderer, std::string image_path, int width, int height, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map, SoundEffect* stomp_sound, Facing start_facing):
    Character(renderer, image_path, width, height, start_position, movement_speed, jump_force, max_jumps, collision_radius, map),
    m_injured(false),
    m_injured_time(0.0f),
    m_stomp_sound(stomp_sound)
{
    m_facing_direction = start_facing;
}

void Enemy::Update(float deltaTime, SDL_Event e)
{
    Character::Update(deltaTime, e);

    // AI
    if (!m_injured)
    {
        DoAIMove();
    }
    else
    {
        // Don't move when injured
        m_moving_left = false;
        m_moving_right = false;

        // Count down injury time
        m_injured_time -= deltaTime;
        if (m_injured_time <= 0.0f)
            ResetFlip();
    }
}

void Enemy::TakeDamage()
{
    m_injured = true;
    m_injured_time = KOOPA_INJURY_TIME;
    m_stomp_sound->Play();
    m_velocity.y = 270.0f;
}

// Not to be confused with a flip reset, that's a different game
void Enemy::ResetFlip()
{
    if (m_facing_direction == Facing::LEFT)
    {
        m_facing_direction = Facing::RIGHT;
    }
    else
    {
        m_facing_direction = Facing::LEFT;
    }

    m_injured = false;
    Jump();
}
