#include "EnemyKoopa.h"


#include "Common.h"
#include "Texture2D.h"

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer, std::string imagePath, SoundEffect* stomp_sound, LevelMap* map, Vector2D start_position, Facing start_facing) :
    Enemy(renderer, imagePath, KOOPA_WIDTH, KOOPA_HEIGHT, start_position, KOOPA_SPEED, KOOPA_INITIAL_JUMP_FORCE, 1, 16.0f, map, stomp_sound, start_facing)
{
    m_sprite->SetAnimation(32, 0, 0.15f, 4);
}

EnemyKoopa::~EnemyKoopa()
{
}

void EnemyKoopa::Update(float deltaTime, SDL_Event e)
{
    Enemy::Update(deltaTime, e);
}


void EnemyKoopa::Render()
{
    Character::Render();    

#ifdef DEBUG_DRAW_ENEMY_BASE
    Rect2D collision = GetCollisionBox();
    int posXCenter = (int)(collision.x + (collision.width * 0.5));
    int posYFoot = (int)(collision.y + (collision.height));
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
    if (posYFoot > 300)
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(m_renderer, posXCenter, posYFoot, posXCenter, posYFoot + 10);
#endif
}

void EnemyKoopa::ResetFlip()
{
    Enemy::ResetFlip();
    m_sprite->SetAnimation(0, 0, 1.0f, 1);
}

void EnemyKoopa::DoAIMove()
{
    // Move according to facing direction, never turn around
    if (m_facing_direction == Facing::LEFT)
    {
        m_moving_left = true;
        m_moving_right = false;
    }
    else if (m_facing_direction == Facing::RIGHT)
    {
        m_moving_left = false;
        m_moving_right = true;
    }
}

void EnemyKoopa::TakeDamage()
{
    Enemy::TakeDamage();
    m_sprite->SetAnimation(0, 32, 1.0f, 1);
}

int EnemyKoopa::GetKillScore()
{
    return KOOPA_KILL_SCORE;
}
