#pragma once
#include "Character.h"
#include "SoundEffect.h"

class Enemy : public Character
{
protected:
    bool m_injured;
    float m_injured_time;

    SoundEffect* m_stomp_sound;

    virtual void ResetFlip();

public:
    Enemy(SDL_Renderer* renderer, std::string image_path, int width, int height, Vector2D start_position, float movement_speed, float jump_force, short max_jumps, float collision_radius, LevelMap* map, SoundEffect* stomp_sound, Facing start_facing);

    void Update(float deltaTime, SDL_Event e) override;
    
    virtual void TakeDamage();
    virtual void DoAIMove() = 0;
    
    bool IsInjured() const { return m_injured; }
    virtual int GetKillScore() = 0;
};
