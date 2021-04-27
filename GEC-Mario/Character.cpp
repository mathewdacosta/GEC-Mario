#include "Character.h"
#include <iostream>


#include "AnimatedSprite.h"
#include "constants.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string image_path, int width, int height, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map) :
    m_renderer(renderer),
    m_position(start_position),
    m_current_level_map(map),
    m_movement_speed(movement_speed),
    m_jump_force(jump_force),
    m_max_jumps(max_jumps),
    m_collision_radius(collision_radius),
    m_facing_direction(Facing::RIGHT),
    m_moving_left(false),
    m_moving_right(false),
    m_jump_ascending(false),
    m_remaining_jumps(max_jumps),
    m_ceiling_headbutt(false),
    m_velocity({ 0.0f, 0.0f }),
    m_alive(true)
{
    m_sprite = new AnimatedSprite(renderer, image_path, width, height);
}

Character::~Character()
{
    m_renderer = nullptr;
    delete m_sprite;
}

void Character::Jump()
{
    m_velocity.y = m_jump_force;
    m_jump_ascending = true;
    m_remaining_jumps -= 1;
}

void Character::MoveLeft(float deltaTime)
{
    m_facing_direction = Facing::LEFT;
    m_position.x -= deltaTime * m_movement_speed;
}

void Character::MoveRight(float deltaTime)
{
    m_facing_direction = Facing::RIGHT;
    m_position.x += deltaTime * m_movement_speed;
}


void Character::ApplyResistance(float deltaTime)
{
    const float deltaResistanceX = (RESISTANCE * deltaTime);
    if (m_velocity.x < 0)
    {
        m_velocity.x = std::min(0.0f, m_velocity.x + deltaResistanceX);
    }
    else if (m_velocity.x > 0)
    {
        m_velocity.x = std::max(0.0f, m_velocity.x - deltaResistanceX);
    }
    
    m_velocity.y -= deltaTime * GRAVITY;
}

bool Character::CanJump()
{
    return m_remaining_jumps > 0;
}

bool Character::IsJumping()
{
    return m_remaining_jumps < m_max_jumps;
}

void Character::CancelJump(bool force)
{
    // If we're still ascending when we collide with something, don't cancel
    if (force || !m_jump_ascending)
    {
        m_remaining_jumps = m_max_jumps;
        m_velocity.y = 0.0f;
    }
}

void Character::Render()
{
    m_sprite->Draw(m_position);

#ifdef DEBUG_DRAW_CHARACTER_BOXES
    SDL_SetRenderDrawColor(m_renderer, 127, 0, 127, 255);
    Rect2D collision = GetCollisionBox();
    SDL_Rect sdlRect = {
        collision.x,
        collision.y,
        collision.width,
        collision.height
    };

    SDL_RenderDrawRect(m_renderer, &sdlRect);
#endif
}

void Character::Update(float deltaTime, SDL_Event e)
{
    HandleInput(deltaTime, e);
    UpdateMovement(deltaTime);
    UpdateSprite(deltaTime);
}

void Character::HandleInput(float deltaTime, SDL_Event e)
{
}

void Character::UpdateMovement(float deltaTime)
{
    // Reset headbutting state
    m_ceiling_headbutt = false;
    
    // Adjust position according to velocity
    m_position.x += m_velocity.x * deltaTime;
    m_position.y -= m_velocity.y * deltaTime;

    // Apply gravity
    ApplyResistance(deltaTime);
    if (m_velocity.y <= 0)
    {
        m_jump_ascending = false;
    }

    Rect2D collisionBox = GetCollisionBox();
    int tileXCenter = (int)(collisionBox.x + (collisionBox.width * 0.5)) / TILE_WIDTH;
    int tileYHead = (int)(collisionBox.y) / TILE_HEIGHT;
    int tileYFoot = (int)(collisionBox.y + collisionBox.height) / TILE_HEIGHT;

    // Stop falling
    if (!m_current_level_map->GetTileAt(tileYFoot, tileXCenter) == 0 && m_alive)
    {
        // Cancel jump
        CancelJump();
    }

    // Collide with tiles above head
    if (m_velocity.y > 0.0f && m_current_level_map->GetTileAt(tileYHead, tileXCenter) == 1)
    {
        m_velocity.y = -120.0f;
        m_ceiling_headbutt = true;
    }

    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }

    // Check if off left/right of screen and wrap around
    if (collisionBox.x < (float)-(collisionBox.width * 0.5f))
    {
        SetPosition(Vector2D(SCREEN_WIDTH - (0.5 * collisionBox.width), collisionBox.y));
    }
    else if (collisionBox.x > SCREEN_WIDTH - (float)(collisionBox.width * 0.5f))
    {
        SetPosition(Vector2D(-0.5f * collisionBox.width, collisionBox.y));
    }
}

void Character::UpdateSprite(float deltaTime)
{
    m_sprite->UpdateAnimation(deltaTime);
    
    if (m_facing_direction == Facing::LEFT)
        m_sprite->SetFlip(SDL_FLIP_HORIZONTAL);
    else
        m_sprite->SetFlip(SDL_FLIP_NONE);
}

void Character::SetPosition(Vector2D new_position)
{
    m_position = new_position;
}

Vector2D Character::GetPosition()
{
    return m_position;
}

float Character::GetCollisionRadius()
{
    return m_collision_radius;
}

Rect2D Character::GetCollisionBox()
{
    return Rect2D(m_position.x, m_position.y, m_sprite->GetSingleFrameWidth(), m_sprite->GetSingleFrameHeight());
}
