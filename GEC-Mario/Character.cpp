#include "Character.h"
#include <iostream>

#include "constants.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string image_path, Vector2D start_position, float movement_speed)
{
    m_renderer = renderer;
    m_position = start_position;
    m_movement_speed = movement_speed;
    
    m_facing_direction = FACING::RIGHT;
    m_moving_left = false;
    m_moving_right = false;
    m_jumping = false;
    m_can_jump = true;
    
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
    m_jump_force = INITIAL_JUMP_FORCE;
    m_jumping = true;
    m_can_jump = false;
}

void Character::MoveLeft(float deltaTime)
{
    m_facing_direction = FACING::LEFT;
    m_position.x -= deltaTime * m_movement_speed;
}

void Character::MoveRight(float deltaTime)
{
    m_facing_direction = FACING::RIGHT;
    m_position.x += deltaTime * m_movement_speed;
}


void Character::AddGravity(float deltaTime)
{
    if (m_position.y + 64 <= SCREEN_HEIGHT)
    {
        m_position.y += deltaTime * GRAVITY;
    }
    else
    {
        m_jumping = false;
        m_can_jump = true;
    }
}

void Character::Render()
{
    SDL_RendererFlip flip;
    if (m_facing_direction == FACING::LEFT)
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
    if (m_jumping)
    {
        // Adjust position for jump
        m_position.y -= m_jump_force * deltaTime;
        // Decrease jump force
        m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
        if (m_jump_force <= 0.0f)
            m_jumping = false;
    }
    else
    {
        AddGravity(deltaTime);
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

void Character::SetPosition(Vector2D new_position)
{
    m_position = new_position;
}

Vector2D Character::GetPosition()
{
    return m_position;
}
