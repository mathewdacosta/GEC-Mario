#pragma once
#include "Character.h"
#include "SoundEffect.h"

class Enemy : public Character
{
protected:
    bool m_injured;
    float m_injured_time;

    SoundEffect* m_stomp_sound;

    void ResetFlip();

    virtual float GetWidth() = 0;
    virtual float GetHeight() = 0;

public:
    Enemy(SDL_Renderer* renderer, std::string image_path, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map, SoundEffect* stomp_sound, Facing start_facing);

    void Update(float deltaTime, SDL_Event e) override;
    
    void TakeDamage();
    virtual void DoAIMove() = 0; 

    Rect2D GetCollisionBox() override;
    
    bool IsInjured() const { return m_injured; }
    virtual int GetKillScore() = 0;
};
