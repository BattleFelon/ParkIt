#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Display
{
public:
	Display();
	~Display();

	void init();
	void run();

private:
	//View Moving code
	void moveView();

	//Event handler
	void eventHandle();

	void togglePlaceRoad(){m_placeRoad = !m_placeRoad;};
	void placeRoad();

    bool m_placeRoad = false;

    sf::Vector2f firstPos;
    sf::Vector2f secondPos;
	const static int M_X = 100;
	const static int M_Y = 200;

	int m_map[M_X][M_Y];

	//Setup Gui Enviroment
	void createGui();

	//Gui Object
	sfg::SFGUI m_sfgui;

	//SFGui varibles
	sfg::Desktop m_desktop;
	sfg::Window::Ptr m_window;

	//SFML varibles
	sf::RenderWindow m_renderWindow;
	sf::Clock m_clock;
	sf::View m_view;
	sf::Event m_event;
	float m_zoom = 1.0f;

	//Iamge, Sprite and Texture Objects
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

