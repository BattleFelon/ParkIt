#pragma once
#include "GameMap.h"

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class MovingObject
{
public:
	MovingObject();
	~MovingObject();

    void init(sf::Vector2f pos, float acc, float maxV, GameMap * gameMap);
    void update();
    sf::Vector2f getPos(){return(m_pos);}

private:
    GameMap * m_gmap;
    sf::Vector2f m_pos;
    sf::Vector2i m_localTarget;
    sf::Vector2i m_globalTaget;
    sf::Vector2f m_vel;

    float m_acc;
    float m_maxV;

};
