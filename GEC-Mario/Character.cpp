#include "Character.h"
#include "Texture2D.h"


Character::Character(SDL_Renderer* renderer, std::string image_path, Vector2D start_position)
{
    m_renderer = renderer;
    m_position = start_position;
    
    m_facing_direction = FACING::RIGHT;
    m_moving_left = false;
    m_moving_right = false;
    
    m_texture = new Texture2D(m_renderer);
    if (!m_texture->LoadFromFile(image_path))
    {
        std::cout << "Failed to load texture " << image_path << std::endl;
    }
}

Character::~Character()
{
    m_renderer = nullptr;
    delete m_texture;
}


void Character::MoveLeft(float deltaTime)
{
    m_facing_direction = FACING::LEFT;
    m_position.x -= 1;
}

void Character::MoveRight(float deltaTime)
{
    m_facing_direction = FACING::RIGHT;
    m_position.x += 1;
}

void Character::Render()
{
    SDL_RendererFlip flip;
    if (m_facing_direction == FACING::LEFT)
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;
    
    m_texture->Render(m_position, flip);
}

void Character::Update(float deltaTime, SDL_Event e)
{
    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }
    
    switch (e.type)
    {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            m_moving_left = true;
            break;
        case SDLK_RIGHT:
            m_moving_right = true;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            m_moving_left = false;
            break;
        case SDLK_RIGHT:
            m_moving_right = false;
            break;
        }
        break;
    }
}

void Character::SetPosition(Vector2D new_position)
{
    m_position = new_position;
}

Vector2D Character::GetPosition()
{
    return m_position;
}
