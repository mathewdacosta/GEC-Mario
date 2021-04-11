#include "EnemyKoopa.h"


#include "Common.h"
#include "Texture2D.h"

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer, std::string imagePath, SoundEffect* stomp_sound, LevelMap* map, Vector2D start_position, Facing start_facing) :
    Enemy(renderer, imagePath, start_position, KOOPA_SPEED, KOOPA_INITIAL_JUMP_FORCE, 1, 16.0f, map, stomp_sound, start_facing)
{
    m_single_sprite_w = m_texture->GetWidth() / 2;
    m_single_sprite_h = m_texture->GetHeight();
}

EnemyKoopa::~EnemyKoopa()
{
}

void EnemyKoopa::Render()
{
    // Position on sprite sheet to draw from
    // first sprite = not injured; second sprite = injured
    int sourceX = m_injured ? m_single_sprite_w : 0.0f;
    SDL_Rect sourceRect = { sourceX, 0, m_single_sprite_w, m_single_sprite_h };
    // Position on screen to draw at
    SDL_Rect destRect = { m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h };

    // Flip and draw in correct direction
    if (m_facing_direction == Facing::RIGHT)
    {
        m_texture->Render(sourceRect, destRect, SDL_FLIP_NONE);
    }
    else
    {
        m_texture->Render(sourceRect, destRect, SDL_FLIP_HORIZONTAL);
    }

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


int EnemyKoopa::GetKillScore()
{
    return KOOPA_KILL_SCORE;
}
