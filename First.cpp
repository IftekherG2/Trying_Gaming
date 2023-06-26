#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<SFML/Audio.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML Game");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Event event;

	//FONT & TEXT//
	sf::Font font;
	if (font.loadFromFile("Data/comici.ttf") == 0) {
		return 1;
	}
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Red);
	score.setPosition(500,0);
	score.setString("00000");

	//IMAGES//
	sf::Texture ladhi;
	if (ladhi.loadFromFile("Data/stickz.png") == -1)return 1;

	sf::Texture image_ball;
	if (image_ball.loadFromFile("Data/ballz.png") == -1) {
		return 1;
	}
	sf::Texture backgi;
	if (backgi.loadFromFile("Data/bgii.png") == 0) {
		return 1;
	}

	//SOUNDS//
	sf::SoundBuffer sbuffer;
	if (sbuffer.loadFromFile("Data/hitball.wav") == 0) {
		return 1;
	}
	sf::SoundBuffer s1buffer;
	if (s1buffer.loadFromFile("Data/Hit_Hurt.wav") == 0)return 1;

	sf::Sound hit;
	hit.setBuffer(sbuffer);
	sf::Sound bhit;
	bhit.setBuffer(s1buffer);
	
	//SHAPES//
	sf::RectangleShape stick;
	stick.setSize(sf::Vector2f(200,30));
	stick.setPosition(400, 560);
	//stick.setFillColor(sf::Color::Green);
	stick.setTexture(&ladhi);

	sf::CircleShape ball;
	ball.setRadius(30);
	ball.setPosition(500, 300);
	ball.setFillColor(sf::Color::White);
	ball.setTexture(&image_ball);
	

	//STATES//
	bool left = false, right = false;

	//VARIBALES//
	int xBall = -3, yBall = -3;
	int xStick = 0;
	int points = 0;
	int spd = -3;
	

	//GAME LOOP//
	bool play = true;
	while (play == true)
	{
		//EVENTS//
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				play = false;
			}
			//KEY PRESSED//
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			{
				left = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			{
				right = true;
			}
			//Key Released//
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
			{
				left = false;
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
			{
				right = false;
			}

		}
		//----->  LOGIC LOGIC LOGIC <------///
		/// MOvements///
		if (left == true)xStick = -5;
		if (right == true)xStick = 5;
		if (left == true && right == true)xStick = 0;
		if (left == false && right == false)xStick = 0;
		
		//CHecking OUT OF BOUNDS//
        stick.move(xStick, 0);
		if (stick.getPosition().x < 0)stick.setPosition(0, 560);
		if (stick.getPosition().x > 800)stick.setPosition(800, 560);
		
		ball.move(xBall, yBall);
		if (ball.getPosition().y < 0) {
			yBall = -yBall;
			bhit.play();
		}
		if (ball.getPosition().x < 0 || ball.getPosition().x > 940) {
			xBall = -xBall;
			bhit.play();
		}
		if (ball.getPosition().y > 540) {
			ball.setPosition(500, 300);
			points -= 3;
		}
		//COLLISION and SCORING SECTOR//
		if (ball.getGlobalBounds().intersects(stick.getGlobalBounds()) == true) {
			yBall = -yBall; points++;
			hit.play();
			if (points > 0 && points % 4 == 0) {
				spd--;
				xBall = spd; yBall = spd;
			}
			if (points < 0) {
				spd = -3;
				xBall = spd; yBall = spd;
			}
		}
		//RENDERING//
		window.clear();
		window.draw(stick);
		window.draw(ball);
		//SCORING//
		std::stringstream marks;
		marks << points;
		score.setString(marks.str());
		window.draw(score);
		window.display();
	}

	window.close();

	return 0;
}

