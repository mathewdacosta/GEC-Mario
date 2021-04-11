#include "CharacterKoopa.h"


#include "Common.h"
#include "Texture2D.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, SoundEffect* stomp_sound, LevelMap* map,
                               Vector2D start_position, Facing start_facing, float movement_speed) :
    Character(renderer, imagePath, start_position, movement_speed, KOOPA_INITIAL_JUMP_FORCE, 1, 16.0f, map),
    m_injured(false),
    m_injured_time(0.0f),
    m_stomp_sound(stomp_sound)
{ 
    m_facing_direction = start_facing;
    
    m_single_sprite_w = m_texture->GetWidth() / 2;
    m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::Render()
{
    // Position on sprite sheet to draw from
    // first sprite = not injured; second sprite = injured
    int src_x = m_injured ? m_single_sprite_w : 0.0f;
    SDL_Rect src_rect = {src_x, 0, m_single_sprite_w, m_single_sprite_h};
    // Position on screen to draw at
    SDL_Rect dest_rect = {m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h};

    // Flip and draw in correct direction
    if (m_facing_direction == Facing::RIGHT)
    {
        m_texture->Render(src_rect, dest_rect, SDL_FLIP_NONE);
    }
    else
    {
        m_texture->Render(src_rect, dest_rect, SDL_FLIP_HORIZONTAL);
    }

#ifdef DEBUG_DRAW_KOOPA_BASE
    Rect2D collision = GetCollisionBox();
    int posXCenter = (int)(collision.x + (collision.width * 0.5));
    int posYFoot = (int)(collision.y + (collision.height));
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
    if (posYFoot > 300)
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(m_renderer, posXCenter, posYFoot, posXCenter, posYFoot + 10);
#endif
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
    Character::Update(deltaTime, e);

    // AI
    if (!m_injured)
    {
        // If not injured, move
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

void CharacterKoopa::TakeDamage()
{
    m_injured = true;
    m_injured_time = KOOPA_INJURY_TIME;
    m_stomp_sound->Play();
}

// Not to be confused with a flip reset, that's a different game
void CharacterKoopa::ResetFlip()
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

Rect2D CharacterKoopa::GetCollisionBox()
{
    return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h);
}
