#include "Character.h"
#include <iostream>

#include "constants.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string image_path, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map)
{
    m_renderer = renderer;
    m_position = start_position;
    m_movement_speed = movement_speed;
    m_collision_radius = collision_radius;
    m_current_level_map = map;
    
    m_facing_direction = Facing::RIGHT;
    m_moving_left = false;
    m_moving_right = false;
    // m_jumping = false;
    // m_can_jump = true;
    m_jump_force = jump_force;
    m_max_jumps = max_jumps;
    m_remaining_jumps = max_jumps;
    m_jump_velocity = 0.0f;
    m_alive = true;
    
    m_texture = new Texture2D(m_renderer);
    if (!m_texture->LoadFromFile(image_path))
    {
        std::cout << "Failed to load texture " << image_path << std::endl;
    }
}

Character::~Character()
{
    m_renderer = nullptr;
    delete m_texture;
}

void Character::Jump()
{
    m_jump_velocity = m_jump_force;
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


void Character::AddGravity(float deltaTime)
{
    m_jump_velocity -= deltaTime * GRAVITY;
}

bool Character::CanJump()
{
    return m_remaining_jumps > 0;
}

bool Character::IsJumping()
{
    return m_remaining_jumps < m_max_jumps;
}

void Character::CancelJump()
{
    m_remaining_jumps = m_max_jumps;
}

void Character::Render()
{
    SDL_RendererFlip flip;
    if (m_facing_direction == Facing::LEFT)
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;
    
    m_texture->Render(m_position, flip);
}
    
void Character::Update(float deltaTime, SDL_Event e)
{
    HandleInput(deltaTime, e);
    UpdateMovement(deltaTime);
}

void Character::UpdateMovement(float deltaTime)
{
    // Adjust position for jump/fall
    m_position.y -= m_jump_velocity * deltaTime;
    AddGravity(deltaTime);

    Rect2D collisionBox = GetCollisionBox();
    int posXCenter = (int) (collisionBox.x + (collisionBox.width * 0.5)) / TILE_WIDTH;
    int posYFoot = (int) (collisionBox.y + collisionBox.height) / TILE_HEIGHT;
    
    if (!m_current_level_map->GetTileAt(posYFoot, posXCenter) == 0)
    {
        // Cancel jump
        CancelJump();

        /* TODO: this is bugged
         *   - we want to stop velocity when character foot touches a solid tile
         *   - don't stop velocity when character first jumps, even if embedded in a tile
         *   - the velocity refactor removed the separate "is currently ascending in a jump" state; maybe add this back in by checking IsJumping && velocity <= 0
         */
        m_jump_velocity = 0.0f;
    }

    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }
}

void Character::HandleInput(float deltaTime, SDL_Event e) {}

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
    return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
}
