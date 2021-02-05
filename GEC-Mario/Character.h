#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "Common.h"

class Texture2D;

class Character
{
protected:
    SDL_Renderer* m_renderer;
    Vector2D m_position;
    Texture2D* m_texture;
    
    FACING m_facing_direction;
    bool m_moving_left;
    bool m_moving_right;
    float m_movement_speed;

    virtual void MoveLeft(float deltaTime);
    virtual void MoveRight(float deltaTime);

public:
    Character(SDL_Renderer* renderer, std::string image_path, Vector2D start_position, float movement_speed);
    ~Character();

    virtual void Render();
    virtual void Update(float deltaTime, SDL_Event e);

    void SetPosition(Vector2D new_position);
    Vector2D GetPosition();
};
