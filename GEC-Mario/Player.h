#pragma once
#include "Character.h"

class Player : public Character
{
protected:
    bool m_jump_held;

    virtual const SDL_Keycode GetLeftKey() = 0;
    virtual const SDL_Keycode GetRightKey() = 0;
    virtual const SDL_Keycode GetJumpKey() = 0;

public:
    Player(SDL_Renderer* renderer, const std::string& image_path, const Vector2D& start_position,
        float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map);

    void HandleInput(float deltaTime, SDL_Event e) override;
};
