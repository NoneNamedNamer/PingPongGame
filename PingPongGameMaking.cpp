#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	// video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window
	RenderWindow window(vm, "Pong", Style::Fullscreen);
	int score = 0;
	int score2 = 0;
	int lives = 3;
	int lives2 = 3;

	// Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1060);

	Bat bat2(1920 / 2, 20);

	// Create a ball
	Ball ball(1920 / 2, 1080 / 2);

	// Create a text object called HUD
	Text hud, hud2;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.TTF");

	// Set the font to our retro-style
	hud.setFont(font);
	hud2.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(30);
	hud2.setCharacterSize(30);

	// Choose a color
	hud.setFillColor(Color::White);
	hud.setPosition(20, 1000);
	hud2.setFillColor(Color::White);
	hud2.setPosition(1700, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		
		Handle the player input
		
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				//Quit the game when the window is closed
				window.close();
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys: 1st bat
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		//2nd bat
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			bat2.moveLeft();
		}
		else
		{
			bat2.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			bat2.moveRight();
		}
		else
		{
			bat2.stopRight();
		}

		/*
		
		Update the bat, the ball and the HUD
		
		*/

		// Update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		bat2.update(dt);
		ball.update(dt);

		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());

		std::stringstream ss2;
		ss2 << "Score:" << score2 << " Lives:" << lives2;
		hud2.setString(ss2.str());

		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();

			// Remove a life
			lives--;

			// Check for zero live
			if (lives < 1)
			{
				// reset the score
				score = 0;

				// reset the lives
				lives = 3;
			}
		}

		

		// Handle the ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundTop();

			// Add a point to the players score
			score++;
		}

		// Handle ball hitting sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Has the ball git the bat?
		if (ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
		}

		/*
		
		Draw the bat, the ball and the HUD
		
		*/

		window.clear();
		window.draw(hud);
		window.draw(hud2);
		window.draw(bat.getShape());
		window.draw(bat2.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}