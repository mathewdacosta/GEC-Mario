#include "PowBlock.h"

#include <iostream>
#include <ostream>

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* level_map)
{
    m_renderer = renderer;
    m_level_map = level_map;
    
    std::string imagePath = "Images/PowBlock.png";
    m_texture = new Texture2D(renderer);
    if (!m_texture->LoadFromFile(imagePath.c_str()))
    {
        std::cout << "Failed to load texture." << std::endl;
        return;
    }

    m_single_sprite_w = m_texture->GetWidth() / 3; // Three sprites in a row
    m_single_sprite_h = m_texture->GetHeight(); // Single row so sprite height = texture height
    m_hits_left = 3;
    m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}

PowBlock::~PowBlock()
{
    m_renderer = nullptr;
    m_level_map = nullptr;
    delete m_texture;
}

void PowBlock::Render()
{
    if (m_hits_left <= 0) return;

    // Create the rect to draw from the sprite sheet
    SDL_Rect src_rect = {
        (m_hits_left - 1) * m_single_sprite_w,
        0,
        m_single_sprite_w,
        m_single_sprite_h
    };

    // Create the rect to draw at on the screen
    Rect2D current_rect = GetCollisionBox();
    SDL_Rect dest_rect = {
        current_rect.x,
        current_rect.y,
        current_rect.width,
        current_rect.height
    };

    m_texture->Render(src_rect, dest_rect, SDL_FLIP_NONE);
}

void PowBlock::TakeHit()
{
    m_hits_left -= 1;
    if (m_hits_left <= 0)
    {
        m_hits_left = 0;
        m_level_map->ChangeTileAt(8, 7, 0);
        m_level_map->ChangeTileAt(8, 8, 0);
    }
}
