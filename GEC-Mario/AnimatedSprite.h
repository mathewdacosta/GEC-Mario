#pragma once
#include "Common.h"
#include "Texture2D.h"

class AnimatedSprite
{
private:
    SDL_Renderer* m_renderer;
    Texture2D* m_spritesheet;
    const bool m_own_spritesheet;
    
    int m_single_frame_width;
    int m_single_frame_height;
    
    int m_animation_start_x;
    int m_animation_y;
    int m_animation_current_frame;
    int m_animation_total_frames;
    float m_animation_frame_duration;
    float m_animation_time_elapsed;
    SDL_RendererFlip m_flip;
    
public:
    AnimatedSprite(SDL_Renderer* renderer, std::string spritesheet_path, int width, int height);
    AnimatedSprite(SDL_Renderer* renderer, Texture2D* spritesheet, int width, int height);
    ~AnimatedSprite();
    
    SDL_RendererFlip GetFlip() { return m_flip; }

    int GetSingleFrameWidth() const;
    void SetSingleFrameWidth(const int single_frame_width);
    int GetSingleFrameHeight() const;
    void SetSingleFrameHeight(const int single_frame_height);
    void SetAnimation(int start_x, int y, float frame_duration, int total_frames, int start_frame = 0);
    void SetFlip(SDL_RendererFlip flip) { m_flip = flip; }
    
    void UpdateAnimation(const float& deltaTime);
    void Draw(const Vector2D& position);
};
