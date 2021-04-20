#pragma once

#include <SDL.h>
#include <string>

#include "AnimatedSprite.h"

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Common.h"
#include "LevelMap.h"

class Texture2D;

class Character
{
protected:
    SDL_Renderer* m_renderer;
    Vector2D m_position;
    AnimatedSprite* m_sprite;
    LevelMap* m_current_level_map;

    const float m_movement_speed;
    const float m_jump_force;
    const short m_max_jumps;
    const float m_collision_radius;
    
    Facing m_facing_direction;
    bool m_moving_left;
    bool m_moving_right;
    bool m_jump_ascending;
    short m_remaining_jumps;
    bool m_ceiling_headbutt;
    
    Vector2D m_velocity;
    bool m_alive;

    virtual void Jump();
    virtual void MoveLeft(float deltaTime);
    virtual void MoveRight(float deltaTime);
    
    void ApplyResistance(float deltaTime);
    bool CanJump();

public:
    Character(SDL_Renderer* renderer, std::string image_path, int width, int height, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map);
    virtual ~Character();

    virtual void Render();
    virtual void Update(float deltaTime, SDL_Event e);

    virtual void HandleInput(float deltaTime, SDL_Event e);
    void UpdateMovement(float deltaTime);
    void UpdateSprite(float deltaTime);

    void SetPosition(Vector2D new_position);
    Vector2D GetPosition();

    float GetCollisionRadius();
    virtual Rect2D GetCollisionBox();

    bool IsJumping();
    void CancelJump(bool force = false);

    bool IsHeadbuttingCeiling() const { return m_ceiling_headbutt; }

    bool IsAlive() { return m_alive; }
    void SetAlive(bool alive) { m_alive = alive; }
};

#endif
