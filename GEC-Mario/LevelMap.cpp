#include "LevelMap.h"

#include <fstream>
#include <iostream>


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

LevelMap* LevelMap::LoadFromFile(std::string path)
{
    int loadedMap[MAP_HEIGHT][MAP_WIDTH] = {};

    std::ifstream inFile(path.c_str());

    if (!inFile || inFile.bad())
    {
        std::cout << "Could not load level map '" << path << "'!" << std::endl;
        return nullptr;
    }

    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            if (inFile.eof())
            {
                std::cout << "Invalid map data! Expected " << MAP_HEIGHT * MAP_WIDTH << " entries, got " << row * MAP_WIDTH + col << " entries." << std::endl;
                inFile.close();
                return nullptr;
            }
            
            inFile >> loadedMap[row][col];
        }
    }

    inFile.close();

    return new LevelMap(loadedMap);
}
