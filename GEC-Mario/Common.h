#pragma once

#include <SDL_rect.h>

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		this->x = x_pos;
		this->y = y_pos;
		this->width = width;
		this->height = height;
	}

	Rect2D(SDL_Rect& sdl_rect)
	{
		this->x = sdl_rect.x;
		this->y = sdl_rect.y;
		this->width = sdl_rect.w;
		this->height = sdl_rect.h;
	}
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL_1,
	SCREEN_LEVEL_2,
	SCREEN_GAME_OVER,
	SCREEN_HIGH_SCORES
};

enum class Facing
{
	LEFT,
	RIGHT
};
