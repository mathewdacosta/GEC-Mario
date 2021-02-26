#pragma once

#include <string>
#include <SDL.h>
#include "Common.h"

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
class Texture2D
{
private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	int m_width;
	int m_height;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0);
	void Render(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
};
#endif
