#include "MovingObject.h"
#include "GameMap.h"
#include "Display.h"

#include <vector>
#include <iostream>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


MovingObject::MovingObject()
{
}


MovingObject::~MovingObject()
{
}

void MovingObject::init(sf::Vector2f pos, float acc, float maxV, GameMap * gameMap){

    int x = pos.x/50;
    int y = pos.y/50;

    if(x > gameMap->getX() || x < 0 || y > gameMap->getY() || y < 0){
        std::cout << "Car out of range \n";
    }
    else{
            if(gameMap->getVal(x,y) == 1){
                m_localTarget = sf::Vector2i(x + 1, y);
                std::cout << x << " " << y << " " << m_localTarget.x << " "<< m_localTarget.y << "\n";
            }
            else if(gameMap->getVal(x,y)  == 2){
                m_localTarget = sf::Vector2i(x, y + 1);
                std::cout << x << " " << y << " " << m_localTarget.x << " "<< m_localTarget.y << "\n";
            }
            else if(gameMap->getVal(x,y)  == 3){
                m_localTarget = sf::Vector2i(x -1, y);
                std::cout << x << " " << y << " " << m_localTarget.x << " "<< m_localTarget.y << "\n";
            }
            else if(gameMap->getVal(x,y)  == 4){
                m_localTarget = sf::Vector2i(x, y - 1);
                std::cout << x << " " << y << " " << m_localTarget.x << " "<< m_localTarget.y << "\n";
            }
        }
        std::cout << x << " " << y << " " << m_localTarget.x << " "<< m_localTarget.y << "\n";

        m_pos = sf::Vector2f(x*50,y*50);
        m_acc = acc;
        m_vel = sf::Vector2f(0,0);
        m_maxV = maxV;
        m_gmap = gameMap;
}


void MovingObject::update(){

    int x = m_pos.x/50;
    int y = m_pos.y/50;

    if(m_gmap->getVal(x,y) == 0){
        m_vel.x = 0;
        m_vel.y = 0;
    }
    else{
            if(m_gmap->getVal(x,y) == 1){
                if(m_vel.x > m_localTarget.x * 50 - m_pos.x)
                m_pos = sf::Vector2f(m_localTarget.x * 50.f, m_localTarget.y * 50.f);
            }
            else if(m_gmap->getVal(x,y)  == 2){
                if(m_vel.y < m_localTarget.y * 50 - m_pos.y)
                m_pos = sf::Vector2f(m_localTarget.x * 50.f, m_localTarget.y * 50.f);
            }
            else if(m_gmap->getVal(x,y)  == 3){
                if(m_vel.x < m_localTarget.x * 50 - m_pos.x)
                m_pos = sf::Vector2f(m_localTarget.x * 50.f, m_localTarget.y * 50.f);
            }
            else if(m_gmap->getVal(x,y)  == 4){
                if(m_vel.y > m_localTarget.y * 50 - m_pos.y)
                m_pos = sf::Vector2f(m_localTarget.x * 50.f, m_localTarget.y * 50.f);
            }

            if(x != m_localTarget.x && y != m_localTarget.y){
                if(x > m_localTarget.x){
                if(m_vel.x < m_maxV && m_vel.x > -1 * m_maxV){
                        m_vel.x -= m_acc * 1/60.f;
                    }
                }
                else{
                    if(m_vel.x < m_maxV && m_vel.x > -1 * m_maxV){
                        m_vel.x += m_acc * 1/60.f;
                    }
                }
                if(y > m_localTarget.y){
                    if(m_vel.y < m_maxV && m_vel.y > -1 * m_maxV){
                        m_vel.y -= m_acc * 1/60.f;
                    }
                }
                else{
                    if(m_vel.y < m_maxV && m_vel.y > -1 * m_maxV){
                        m_vel.y += m_acc * 1/60.f;
                    }
                }
            }
        }

        m_pos.x += m_vel.x;
        m_pos.y += m_vel.y;
        std::cout << m_vel.x << " " << m_vel.y << "\n";
        std::cout << m_pos.x << " " << m_pos.y << " " << m_localTarget.x << " " << m_localTarget.y << " " << x << " " << y << "\n";
}
