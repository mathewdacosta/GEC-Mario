#pragma once
#include "LevelMap.h"
#include "Texture2D.h"

class PowBlock
{
private:
    SDL_Renderer* m_renderer;
    Vector2D m_position;
    Texture2D* m_texture;
    LevelMap* m_level_map;

    float m_single_sprite_w;
    float m_single_sprite_h;
    int m_hits_left;

public:
    PowBlock(SDL_Renderer* renderer, LevelMap* level_map);
    ~PowBlock();

    void Render();

    Rect2D GetCollisionBox() const { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h); }
    void TakeHit();
    bool IsAvailable() const { return m_hits_left > 0; }
};
