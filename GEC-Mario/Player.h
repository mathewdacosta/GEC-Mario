#pragma once
#include "Character.h"
#include "SoundEffect.h"

enum class PlayerAnimationState
{
    STATIONARY,
    WALKING,
    JUMPING,
    DYING
};

class Player : public Character
{
private:
    SoundEffect* m_jump_sound;
    PlayerAnimationState m_current_animation_state;
    bool m_game_over;

    void SetAnimationState(PlayerAnimationState state);

protected:
    bool m_jump_held;

    virtual const SDL_Keycode GetLeftKey() = 0;
    virtual const SDL_Keycode GetRightKey() = 0;
    virtual const SDL_Keycode GetJumpKey() = 0;

public:
    Player(SDL_Renderer* renderer, const std::string& image_path, int width, int height, const Vector2D& start_position,
        float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map,
        SoundEffect* jump_sound);

    void HandleInput(float deltaTime, SDL_Event e) override;

    void Update(float deltaTime, SDL_Event e) override;
	void Jump() override;

    void Kill();
    bool IsGameOver() const;
};
