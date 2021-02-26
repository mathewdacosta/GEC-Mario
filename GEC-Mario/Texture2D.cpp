#include "Texture2D.h"

#include <iostream>
#include <SDL_image.h>


Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_texture = nullptr;
	m_width = 0;
	m_height = 0;
}

Texture2D::~Texture2D()
{
	// Free up memory
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	// Remove memory used for previous texture
	Free();

	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface == nullptr)
	{
		std::cout << "Could not create surface from file. Error: " << IMG_GetError();
		return false;
	}

	// Colour key image to be transparent
	SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));

	m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
	if (m_texture == nullptr)
	{
		std::cout << "Could not create texture from surface. Error: " << SDL_GetError();
	}

	// Set width and height
	m_width = p_surface->w;
	m_height = p_surface->h;
	
	// Remove loaded surface now we have a texture
	SDL_FreeSurface(p_surface);

	return m_texture != nullptr;
}

void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	// Position to render texture
	SDL_Rect renderLocation = { new_position.x, new_position.y, m_width, m_height };

	// Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
}

void Texture2D::Render(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_RendererFlip flip, double angle)
{
	// Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &dest_rect, angle, nullptr, flip);
}
