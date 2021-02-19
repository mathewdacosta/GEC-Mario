#include "LevelMap.h"


LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
    // Allocate arrays
    m_map = new int* [MAP_HEIGHT];
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        m_map[i] = new int[MAP_WIDTH];
    }

    // Populate arrays
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_WIDTH; j++)
        {
            m_map[i][j] = map[i][j];
        }
    }
}

LevelMap::~LevelMap()
{
    // Delete inner row arrays
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        delete[] m_map[i];
    }
    // Delete outer array
    delete[] m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
    if (h < MAP_HEIGHT && w < MAP_WIDTH)
    {
        return m_map[h][w];
    }

    return 0;
}


void LevelMap::ChangeTileAt(unsigned row, unsigned column, unsigned new_value)
{
    m_map[row][column] = new_value;
}
