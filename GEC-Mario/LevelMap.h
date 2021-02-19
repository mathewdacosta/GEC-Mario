#pragma once

#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "constants.h"

class LevelMap
{
private:
    int** m_map;

public:
    LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
    ~LevelMap();

    int GetTileAt(unsigned int h, unsigned int w);
    void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);
};

#endif
