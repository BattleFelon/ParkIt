#include "Display.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <random>
#include <math.h>

Display::Display()
{
}


Display::~Display()
{
}

void Display::init()
{
	//Set Window and View varibles
	m_renderWindow.create(sf::VideoMode(800, 600), "ParkIt");
	m_view = m_renderWindow.getDefaultView();
	m_renderWindow.setFramerateLimit(60);

	for(int i = 0; i < M_X; ++i){
		for(int j = 0; j < M_Y;++j){
			m_map[i][j] = 1;
		}
	}

	createGui();
}

void Display::run()
{

    sf::CircleShape shape1(25);
    shape1.setFillColor(sf::Color(150, 50, 250));

    sf::CircleShape shape2(25);
    shape2.setFillColor(sf::Color(100, 250, 100));

    sf::CircleShape shape3(25);
    shape2.setFillColor(sf::Color(200, 0, 100));

    sf::RectangleShape car((sf::Vector2f(25,50)));
    car.setFillColor(sf::Color::Red);
    car.setOrigin(sf::Vector2f(car.getSize().x/2,car.getSize().y/2));
    car.setPosition(sf::Vector2f(M_X/2*50, M_Y/2*50));

	while (m_renderWindow.isOpen())
	{
		moveView();
		eventHandle();

		//Update GUI
        m_desktop.Update( 0.f );

		//Set view
		m_renderWindow.setView(m_view);

		//Clear previous frame
		m_renderWindow.clear();
        car.move(sf::Vector2f(rand() % 10 -5,rand() % 10 -5));

		for(int i = 0; i < M_X; ++i){
			for(int j = 0; j < M_Y;++j){
                if(m_placeRoad && (int)firstPos.x/50 >=0 && (int)firstPos.y/50 >=0 && (int)firstPos.x/50 < M_Y && (int)firstPos.y/50 < M_Y){
                    m_map[(int)floor(firstPos.x /50)][(int)floor(firstPos.y/50)] = 2;
                }

                if(car.getPosition().x > i*50 && car.getPosition().y > j*50 && car.getPosition().x < i *51 && car.getPosition().y < j*51)
                    m_map[i][j] = 3;

                    if(m_map[i][j] == 1){
				shape1.setPosition(sf::Vector2f(i*50,j*50));
				m_renderWindow.draw(shape1);
				}
				else if(m_map[i][j] == 2){
                shape2.setPosition(sf::Vector2f(i*50,j*50));
                m_renderWindow.draw(shape2);
				}
				else if(m_map[i][j] ==3){
				shape3.setPosition(sf::Vector2f(i*50,j*50));
				m_renderWindow.draw(shape3);
				}
			}
		}

		//Drawing goes here----------------------------------------------------------

		//Show render windows
		m_sfgui.Display(m_renderWindow);
		m_renderWindow.display();
	}
}

void Display::moveView()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_view.move(sf::Vector2f(0.f, -20.0f*m_zoom));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_view.move(sf::Vector2f(0.f, 20.0f * m_zoom));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_view.move(sf::Vector2f(-20.f * m_zoom, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_view.move(sf::Vector2f(20.f * m_zoom, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_view.rotate(2.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		m_view.rotate(-2.0f);
	}
}

void Display::eventHandle()
{
	while (m_renderWindow.pollEvent(m_event))
	{
		//Gui Event Handler
		m_desktop.HandleEvent( m_event );

		// "close requested" event: we close the m_renderWindow
		if (m_event.type == sf::Event::Closed)
			m_renderWindow.close();

		// catch the resize events
		if (m_event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, (float)m_event.size.width, (float)m_event.size.height);
			m_renderWindow.setView(sf::View(visibleArea));
			m_view = m_renderWindow.getView();
		}

		//Wheel Moving Listener
		if (m_event.type == sf::Event::MouseWheelMoved)
		{

			if (m_event.mouseWheel.delta > 0)
			{
				m_zoom *= .90f;
				m_view.zoom(.9f);
			}
			else if (m_event.mouseWheel.delta < 0)
			{
				m_zoom /= .90f;
				m_view.zoom(1.f / .9f);
			}
		}

		if(m_event.type == sf::Event::MouseButtonPressed && m_placeRoad){
            sf::Vector2i mouse = sf::Mouse::getPosition(m_renderWindow);
            std::cout << mouse.x << " " << mouse.y << '\n';
            firstPos = m_renderWindow.mapPixelToCoords(mouse,m_view);
            std::cout << firstPos.x << " " << firstPos.y << '\n';

		}
		if(m_event.type == sf::Event::MouseButtonReleased && m_placeRoad){
            sf::Vector2i mouse = sf::Mouse::getPosition(m_renderWindow);
            secondPos = m_renderWindow.mapPixelToCoords(mouse,m_view);
		}
	}
}

void Display::createGui()
{

	// We have to do this because we don't use SFML to draw.
	m_renderWindow.resetGLStates();

	m_desktop.SetProperty( "Button#Button", "FontSize", 18.f );
	auto m_button = sfg::Button::Create("Place Road");
	m_button->SetId("Place_Road");

		//Create Settings Window
	m_window = sfg::Window::Create();
	m_window->SetTitle( "Builder" );

    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.f );
	box->Pack( m_button, false );
	m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &Display::togglePlaceRoad, this ) );

	m_window->Add(box);
	m_desktop.Add(m_window);
}

