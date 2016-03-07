
#include "GameMap.h"
#include "Display.h"
#include "MovingObject.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

	createGui();
	m_gameMap.init(500,500);
	//Sprite info
    m_texture.loadFromFile("arrow.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(25,25);
	m_placeRoad = false;
	m_leftDown = false;
	m_mouseMove = false;
}

void Display::run()
{
    std::vector<sf::CircleShape> shapes;

    for(int i = 0; i < 10; ++i){
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color(i*20, 50, 250-i*20));
    shapes.push_back(shape);
    }


    sf::CircleShape carSprite(10);
    carSprite.setFillColor(sf::Color::Magenta);
    MovingObject car;
    car.init(sf::Vector2f(123,135),4,4,&m_gameMap);

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
        sf::Clock clock;

        //Culling Code
        int endCullX = (m_renderWindow.getView().getSize().x + m_renderWindow.getView().getCenter().x )/50 + 10;
        int startCullX = (m_renderWindow.getView().getCenter().x - m_renderWindow.getView().getSize().x/2)/50;
        int endCullY = (m_renderWindow.getView().getSize().y  + m_renderWindow.getView().getCenter().y)/50 + 10;
        int startCullY = (m_renderWindow.getView().getCenter().y - m_renderWindow.getView().getSize().y/2)/50;


        //Low Bounds
        if(endCullX + startCullX < 0)
            endCullX = 0;

        if(endCullY + startCullY < 0)
            endCullY = 0;

        if(startCullX < 0)
            startCullX = 0;

        if(startCullY < 0)
            startCullY = 0;

        //High Bounds
        if(endCullX + startCullX > m_gameMap.getX())
            endCullX = m_gameMap.getX();

        if(endCullY + startCullY > m_gameMap.getY())
            endCullY = m_gameMap.getY();

        if(startCullX > m_gameMap.getX())
            startCullX = m_gameMap.getX();

        if(startCullY > m_gameMap.getY())
            startCullY = m_gameMap.getY();

       for(register int i = startCullX, n = endCullX; i < n; ++i){
           for(register int j = startCullY, m = endCullY; j < m; ++j){
                switch(m_gameMap.getVal(i,j)){

                case 0:
                    shapes[0].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[0]);
                    break;

                case 1:
                    m_sprite.setPosition(i*50+25, j*50+25);
                    m_sprite.setRotation(0);
                    m_renderWindow.draw(m_sprite);
                    break;

                case 2:
                    m_sprite.setPosition(i*50+25, j*50+25);
                    m_sprite.setRotation(270);
                    m_renderWindow.draw(m_sprite);
                    break;

                case 3:
                    m_sprite.setPosition(i*50+25, j*50+25);
                    m_sprite.setRotation(180);
                    m_renderWindow.draw(m_sprite);
                    break;

                case 4:
                    m_sprite.setPosition(i*50+25, j*50+25);
                    m_sprite.setRotation(90);
                    m_renderWindow.draw(m_sprite);
                    break;

                case 5:
                    shapes[5].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[5]);
                    break;

                case 6:
                    shapes[6].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[6]);
                    break;

                case 7:
                    shapes[7].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[7]);
                    break;

                case 8:
                    shapes[8].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[8]);
                    break;

                case 9:
                    shapes[9].setPosition(i*50, j*50);
                    m_renderWindow.draw(shapes[9]);
                    break;
                }
            }
        }

        carSprite.setPosition(car.getPos());
        m_renderWindow.draw(carSprite);
        car.update();
        //std::cout << clock.getElapsedTime().asMicroseconds() << " " << m_zoom <<  "\n";
		//Drawing goes here----------------------------------------------------------

		//Show render windows
		m_sfgui.Display(m_renderWindow);
		m_renderWindow.display();
	}

	std::cout << " Program Terminated \n";
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
			m_zoom = 0.0f;
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
            if(m_event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i mouse = sf::Mouse::getPosition(m_renderWindow);
                firstPos = m_renderWindow.mapPixelToCoords(mouse,m_view);
                m_gameMap.changVal(firstPos.x,firstPos.y,1);
                m_leftDown = true;
            }
		}

         if(m_event.type == sf::Event::MouseMoved && m_leftDown){
                sf::Vector2i mouse = sf::Mouse::getPosition(m_renderWindow);
                currentPos = m_renderWindow.mapPixelToCoords(mouse,m_view);

                if(abs(currentPos.x - firstPos.x) >= abs(currentPos.y - firstPos.y)){
                    if(currentPos.x - firstPos.x >=0)
                        m_gameMap.changVal(currentPos.x,currentPos.y,1);
                    else
                        m_gameMap.changVal(currentPos.x,currentPos.y,3);
                }

                else{
                    if(currentPos.y - firstPos.y >=0)
                        m_gameMap.changVal(currentPos.x,currentPos.y,4);
                    else
                        m_gameMap.changVal(currentPos.x,currentPos.y,2);
                }
                m_mouseMove = true;
        }

        if(m_event.type == sf::Event::MouseButtonReleased && m_mouseMove){
                sf::Vector2i mouse = sf::Mouse::getPosition(m_renderWindow);
                secondPos = m_renderWindow.mapPixelToCoords(mouse,m_view);
                m_leftDown = false;
                m_mouseMove = false;
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

