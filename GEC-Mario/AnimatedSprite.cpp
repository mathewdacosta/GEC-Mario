#include "AnimatedSprite.h"

#include <iostream>
#include "Texture2D.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, std::string spritesheet_path, int width, int height) :
    m_renderer(renderer),
    m_own_spritesheet(true),
    m_single_frame_width(width),
    m_single_frame_height(height),
    m_animation_start_x(0),
    m_animation_y(0),
    m_animation_current_frame(0),
    m_animation_total_frames(1),
    m_animation_frame_duration(1.0f),
    m_animation_time_elapsed(0.0f),
    m_flip(SDL_FLIP_NONE)
{
    m_spritesheet = new Texture2D(renderer);
    if (!m_spritesheet->LoadFromFile(spritesheet_path))
    {
        std::cout << "Could not load spritesheet from path '" << spritesheet_path << "'!" << std::endl;
    }
}


AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, Texture2D* spritesheet, int width, int height) :
    m_renderer(renderer),
    m_spritesheet(spritesheet),
    m_own_spritesheet(false),
    m_single_frame_width(width),
    m_single_frame_height(height),
    m_animation_start_x(0),
    m_animation_y(0),
    m_animation_current_frame(0),
    m_animation_total_frames(1),
    m_animation_frame_duration(1.0f),
    m_animation_time_elapsed(0.0f),
    m_flip(SDL_FLIP_NONE)
{
}

AnimatedSprite::~AnimatedSprite()
{
    if (m_own_spritesheet)
    {
        delete m_spritesheet;
    }
}

int AnimatedSprite::GetSingleFrameWidth() const
{
    return m_single_frame_width;
}

void AnimatedSprite::SetSingleFrameWidth(const int single_frame_width)
{
    m_single_frame_width = single_frame_width;
}

int AnimatedSprite::GetSingleFrameHeight() const
{
    return m_single_frame_height;
}

void AnimatedSprite::SetSingleFrameHeight(const int single_frame_height)
{
    m_single_frame_height = single_frame_height;
}

void AnimatedSprite::SetAnimation(int start_x, int y, float frame_duration, int total_frames, int start_frame)
{
    m_animation_start_x = start_x;
    m_animation_y = y;
    m_animation_frame_duration = frame_duration;
    m_animation_total_frames = total_frames;
    m_animation_current_frame = start_frame;
    m_animation_time_elapsed = 0.0f;
}

void AnimatedSprite::UpdateAnimation(const float& deltaTime)
{
    m_animation_time_elapsed += deltaTime;
    if (m_animation_time_elapsed >= m_animation_frame_duration)
    {
        m_animation_time_elapsed = 0.0f;
        m_animation_current_frame = (m_animation_current_frame + 1) % m_animation_total_frames; 
    }
}

void AnimatedSprite::Draw(const Vector2D& position)
{
    SDL_Rect spriteSource = {
        m_animation_start_x + (m_single_frame_width * m_animation_current_frame),
        m_animation_y,
        m_single_frame_width,
        m_single_frame_height
    };

    SDL_Rect spriteDest = {
        position.x,
        position.y,
        m_single_frame_width,
        m_single_frame_height
    };
    
    m_spritesheet->Render(spriteSource, spriteDest, m_flip);
}
