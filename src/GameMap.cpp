#include "GameMap.h"
#include <vector>
#include <iostream>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::init(int mapX,int mapY){

    m_map_x = mapX;
    m_map_y = mapY;

    m_map.resize(m_map_x);
    for(register int i = 0; i < m_map_x; i++){
        m_map[i].resize(m_map_y);
    }



    for(int i = 0, n = m_map_x; i < n; i++){
        for(int j = 0, m = m_map_y; j < m; j++){
            m_map[i][j] = 0;

        }
    }

}

void GameMap::changVal(int x, int y, int type){

if(x >= 0 && y >= 0 && x <= m_map_x -1 && y <= m_map_y -1)
    m_map[x][y] = type;
}

void GameMap::changVal(float x, float y, int type){
x = x/50;
y = y/50;
if(x >= 0 && y >= 0 && x <= m_map_x -1 && y <= m_map_y -1)
    m_map[x][y] = type;
}
