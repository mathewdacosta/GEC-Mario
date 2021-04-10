#pragma once

#include <string>
#include <SDL_ttf.h>

#include "Common.h"
#include "Font.h"

enum class TextAlignHorizontal
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};

enum class TextAlignVertical
{
    TOP = 0,
    CENTER = 1,
    BOTTOM = 2
};

namespace TextColor
{
    const SDL_Color WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
    const SDL_Color BLACK = { 0x00, 0x00, 0x00, 0xFF };
}

/// <summary> A TTF font with a given size. </summary>
class Font
{
private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    int m_size_pt;

    void DrawToRenderer(SDL_Surface* text_surface, SDL_Rect* destRect) const;

public:
    Font(SDL_Renderer* renderer, std::string path, int pt = 16, int index = 0);
    ~Font();

    bool IsLoaded() const { return m_font != nullptr; }
    int GetSize() const { return m_size_pt; }

    SDL_Rect CalculateDestRect(std::string text, Vector2D& position, TextAlignHorizontal x_align, TextAlignVertical y_align) const;
    
    void DrawSolid(std::string text, Vector2D position, SDL_Color color = TextColor::WHITE, TextAlignHorizontal x_align = TextAlignHorizontal::LEFT, TextAlignVertical y_align = TextAlignVertical::TOP) const;
    void DrawShaded(std::string text, Vector2D position, SDL_Color fg_color = TextColor::WHITE, SDL_Color bg_color = TextColor::BLACK, TextAlignHorizontal x_align = TextAlignHorizontal::LEFT, TextAlignVertical y_align = TextAlignVertical::TOP) const;
    void DrawBlended(std::string text, Vector2D position, SDL_Color color = TextColor::WHITE, TextAlignHorizontal x_align = TextAlignHorizontal::LEFT, TextAlignVertical y_align = TextAlignVertical::TOP) const;
};
