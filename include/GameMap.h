#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class GameMap
{
public:
	GameMap();
	~GameMap();

    int getX(){return(m_map_x-1);};
    int getY(){return(m_map_y-1);};

    void init(int,int);

    int getVal(int x, int y){return m_map[x][y];};
    void changVal(int x,int y, int type);
    void changVal(float x,float y, int type);


private:

    int m_map_x;
    int m_map_y;

    std::vector<std::vector<int>> m_map;
};
