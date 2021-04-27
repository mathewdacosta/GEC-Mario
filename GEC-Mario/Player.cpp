#include "Player.h"

Player::Player(SDL_Renderer* renderer, const std::string& image_path, int width, int height,
               const Vector2D& start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius,
               LevelMap* map, SoundEffect* jump_sound) :
        Character(renderer, image_path, width, height, start_position, movement_speed, jump_force, max_jumps, collision_radius, map),
		m_jump_held(false),
		m_jump_sound(jump_sound),
        m_game_over(false)
{
}

void Player::SetAnimationState(PlayerAnimationState state)
{
    if (state != m_current_animation_state)
    {
        m_current_animation_state = state;
        switch (state)
        {
        case PlayerAnimationState::JUMPING:
            m_sprite->SetAnimation(0, 42, 1.0f, 1);
            break;
        case PlayerAnimationState::WALKING:
            m_sprite->SetAnimation(0, 0, 0.08f, 4);
            break;
        case PlayerAnimationState::DYING:
            m_sprite->SetAnimation(96, 42, 1.0f, 1);
            break;
        case PlayerAnimationState::STATIONARY:
        default:
            m_sprite->SetAnimation(0, 0, 1.0f, 1);
            break;
        }
    }
}

void Player::HandleInput(float deltaTime, SDL_Event e)
{
    if (!m_alive)
    {
        m_moving_left = false;
        m_moving_right = false;
        m_jump_held = false;
        return;
    }
    
    switch (e.type)
    {
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == GetLeftKey())
        {
            m_moving_left = true;
        }
        else if (e.key.keysym.sym == GetRightKey())
        {
            m_moving_right = true;
        }
        else if (e.key.keysym.sym == GetJumpKey())
        {
            if (CanJump() && !m_jump_held)
            {
                m_jump_held = true;
                Jump();
            }
        }
        break;
    case SDL_KEYUP:
        if (e.key.keysym.sym == GetLeftKey())
        {
            m_moving_left = false;
        }
        else if (e.key.keysym.sym == GetRightKey())
        {
            m_moving_right = false;
        }
        else if (e.key.keysym.sym == GetJumpKey())
        {
            m_jump_held = false;
        }
        break;
    }
}

void Player::Update(float deltaTime, SDL_Event e)
{
    Character::Update(deltaTime, e);

    if (!m_alive)
    {
        SetAnimationState(PlayerAnimationState::DYING);
        if (m_position.y > SCREEN_HEIGHT)
            m_game_over = true;
    }
    else if (m_velocity.y > 0)
        SetAnimationState(PlayerAnimationState::JUMPING);
    else if (m_moving_left || m_moving_right)
        SetAnimationState(PlayerAnimationState::WALKING);
    else
        SetAnimationState(PlayerAnimationState::STATIONARY);
}

void Player::Jump()
{
    Character::Jump();
    m_jump_sound->Play(0);
}

void Player::Kill()
{
    if (m_alive)
    {
        m_alive = false;
        m_velocity.y = 300;
    }
}

bool Player::IsGameOver() const
{
    return m_game_over;
}
