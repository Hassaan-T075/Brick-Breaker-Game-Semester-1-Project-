#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<iostream>
#include<vector>
#include<time.h>
#include<sstream>
#include<fstream>
#include<windows.h>

using namespace std;
int vectori[5][8];

//lives
float lives = 3;

//score
float score = 0;

vector<vector<int>> vec = { {1,2,3,4,5,6,7,8},{9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24},{25,26,27,28,29,30,31,32},{33,34,35,36,37,38,39,40} };

void menu(sf::RenderWindow& window);

void gameloop(sf::RenderWindow& window, bool loadgames);

void vecta(vector<vector<int>>& vect); //initialise vector

void highscore(sf::RenderWindow& window);

void loadgame();

int main()
{
	sf::RenderWindow window(sf::VideoMode(1376, 768), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	menu(window);

	return 0;
}

void menu(sf::RenderWindow& window)
{
	bool loadgames = true;

	int MAX_NUMBER_OF_ITMES = 5;

	sf::Font font;
	font.loadFromFile("Sketch3D.woff");

	sf::Text text[5];
	text[0].setFont(font);
	text[0].setString("Brick Demolition");
	text[0].setCharacterSize(80);
	text[0].setFillColor(sf::Color(244.0, 194.0, 194.0));
	text[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
	text[0].setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / (MAX_NUMBER_OF_ITMES + 1) * 1));

	text[1].setFont(font);
	text[1].setString("Start a new Game");
	text[1].setCharacterSize(60);
	text[1].setFillColor(sf::Color(244.0, 194.0, 194.0));
	text[1].setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / (MAX_NUMBER_OF_ITMES + 1) * 2));

	text[2].setFont(font);
	text[2].setString("Load a Game");
	text[2].setCharacterSize(60);
	text[2].setFillColor(sf::Color(244.0, 194.0, 194.0));
	text[2].setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / (MAX_NUMBER_OF_ITMES + 1) * 3));

	text[3].setFont(font);
	text[3].setString("Highscores");
	text[3].setCharacterSize(60);
	text[3].setFillColor(sf::Color(244.0, 194.0, 194.0));
	text[3].setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / (MAX_NUMBER_OF_ITMES + 1) * 4));

	text[4].setFont(font);
	text[4].setString("Exit");
	text[4].setCharacterSize(60);
	text[4].setFillColor(sf::Color(244.0, 194.0, 194.0));
	text[4].setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / (MAX_NUMBER_OF_ITMES + 1) * 5));

	int index = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (index - 1 > 0)
					{
						text[index].setFillColor(sf::Color(244.0, 194.0, 194.0));
						index--;
						text[index].setFillColor(sf::Color::White);
					}
					break;

				case sf::Keyboard::Down:
					if (index + 1 < MAX_NUMBER_OF_ITMES)
					{
						text[index].setFillColor(sf::Color(244.0, 194.0, 194.0));
						index++;
						text[index].setFillColor(sf::Color::White);
					}
					break;
				case (sf::Keyboard::Enter):
					if (index == 1)
						gameloop(window, !loadgames);
					if (index == 2) {
						loadgame();
						gameloop(window, loadgames);
					}
					if (index == 3)
						highscore(window);
					if (index == 4) {
						window.close();
					}
				}
				break;

			case sf::Event::Closed:
				window.close();

				break;
			}
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < MAX_NUMBER_OF_ITMES; i++)
		{
			window.draw(text[i]);
		}
		window.display();
	}

}

void gameloop(sf::RenderWindow& window, bool loadgames)
{
	if (loadgames == false) {
		vecta(vec);
	}
	else {
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				vec[i][j] = vectori[i][j];
			}

		}
	}
	bool gamecomplete = false;

	sf::Text stats[4];

	sf::Font font;
	font.loadFromFile("Sketch3D.woff");

	stats[0].setFont(font);
	stats[0].setString("Score");
	stats[0].setCharacterSize(40);
	stats[0].setFillColor(sf::Color::Blue);
	stats[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
	stats[0].setPosition(sf::Vector2f(window.getSize().x - 250, window.getSize().y / (2 + 7) * 1));

	stats[1].setFont(font);
	stats[1].setString("Lives");
	stats[1].setCharacterSize(40);
	stats[1].setFillColor(sf::Color::Blue);
	stats[1].setStyle(sf::Text::Bold | sf::Text::Underlined);
	stats[1].setPosition(sf::Vector2f(window.getSize().x - 250, window.getSize().y / (2 + 3) * 2));

	stats[2].setFont(font);
	stats[2].setCharacterSize(40);
	stats[2].setFillColor(sf::Color::White);
	stats[2].setStyle(sf::Text::Bold);
	stats[2].setPosition(sf::Vector2f(window.getSize().x - 200, window.getSize().y / (2 + 8) * 2));

	stats[3].setFont(font);
	stats[3].setCharacterSize(40);
	stats[3].setFillColor(sf::Color::White);
	stats[3].setStyle(sf::Text::Bold);
	stats[3].setPosition(sf::Vector2f(window.getSize().x - 200, window.getSize().y / (2 + 2) * 2));

	// the angle at which ball is moving currently
	int ballAngle = 90;

	//paddle position in y direction is constant and only x direction is changing
	float paddlePositionX = 334.0;

	//Ball has both x and y coordinates
	float BallX = 379.0;
	float BallY = 695.0;

	//Paddle divisors
	float left = 334.0;
	float leftCenter = 354.0;
	float Center = 374.0;
	float rightCenter = 394.0;
	float right = 414.0;

	//check is ball hit corner in x direction
	float movingRightwards = false;
	float movingUpwards = true;

	//create player paddle
	sf::RectangleShape playerPaddle(sf::Vector2f(100.0f, 10.0f));
	playerPaddle.setFillColor(sf::Color::Blue);
	playerPaddle.setPosition(sf::Vector2f(334.0f, 700.0f));

	//create playing area border
	sf::RectangleShape border(sf::Vector2f(5.0f, 1376.0f));
	border.setFillColor(sf::Color::Magenta);
	border.setPosition(sf::Vector2f(1000.0f, 0.0f));

	//create boll
	sf::CircleShape ball(10);
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(sf::Vector2f(374.0f, 680.0f));

	bool start = false;

	float MAX_NUMBER_OF_BRICKS = 8.0;

	vector<sf::RectangleShape> brickset(40);
	vector<sf::CircleShape> triangle(10);
	vector<sf::CircleShape> circle(10);
	vector<sf::CircleShape> tri1(10);   // tri1 and tri2 make parallelograms
	vector<sf::CircleShape> tri2(10);
	vector<sf::RectangleShape> innerbrickbrick(10);

	float fac = 4.2;
	float k = 0;
	float type1 = 0, type2 = 0, type3 = 0, type_3 = 0, type4 = 0;
	for (float i = 0; i < 5; i++)
	{
		for (float j = 0; j < 8; j++)

			if (vec[i][j] < 6 && vec[i][j] > -1)
			{
				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));
				brickset[k].setPosition(sf::Vector2f(500.0 / (MAX_NUMBER_OF_BRICKS + fac) * (3.0 * j + 0.5), window.getSize().y / 16 * (i + 1)));

				k++;
			}
			else if (vec[i][j] == 6)
			{
				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));

				brickset[k].setPosition(sf::Vector2f(500.0 / (MAX_NUMBER_OF_BRICKS + fac) * (3.0 * j + 0.5), window.getSize().y / 16 * (i + 1)));

				triangle[type1].setRadius(12.0f);
				triangle[type1].setFillColor(sf::Color::Red);
				triangle[type1].setPosition(sf::Vector2f(brickset[k].getPosition().x + 64.0, brickset[k].getPosition().y + 22.0));
				triangle[type1].setPointCount(3);
				triangle[type1].rotate(180.0f);

				type1++;
				k++;
			}
			else if (vec[i][j] == 7)
			{
				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));

				brickset[k].setPosition(sf::Vector2f(500.0 / (MAX_NUMBER_OF_BRICKS + fac) * (3.0 * j + 0.5), window.getSize().y / 16 * (i + 1)));

				circle[type2].setRadius(10.0f);
				circle[type2].setFillColor(sf::Color::Green);
				circle[type2].setPosition(sf::Vector2f(brickset[k].getPosition().x + 40.0, brickset[k].getPosition().y + 1.8));
				type2++;
				k++;
			}
			else if (vec[i][j] == 8)
			{
				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));

				brickset[k].setPosition(sf::Vector2f(500.0 / (MAX_NUMBER_OF_BRICKS + fac) * (3.0 * j + 0.5), window.getSize().y / 16 * (i + 1)));

				tri1[type3].setRadius(12.0f);
				tri1[type3].setFillColor(sf::Color::Yellow);
				tri1[type3].setPosition(sf::Vector2f(brickset[k].getPosition().x + 67.5, brickset[k].getPosition().y + 21.9));
				tri1[type3].setPointCount(3);
				tri1[type3].rotate(180.0f);

				tri2[type_3].setRadius(12.0f);
				tri2[type_3].setFillColor(sf::Color::Yellow);
				tri2[type_3].setPosition(sf::Vector2f(brickset[k].getPosition().x + 33.5, brickset[k].getPosition().y + 3.7));
				tri2[type_3].setPointCount(3);

				type3++;
				type_3++;
				k++;
			}
			else if (vec[i][j] == 9)
			{

				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));

				brickset[k].setPosition(sf::Vector2f(500.0 / (MAX_NUMBER_OF_BRICKS + fac) * (3.0 * j + 0.5), window.getSize().y / 16 * (i + 1)));

				innerbrickbrick[type4].setSize(sf::Vector2f(80.0f, 15.0f));
				innerbrickbrick[type4].setFillColor(sf::Color::Color(128, 128, 128, 255));
				innerbrickbrick[type4].setPosition(sf::Vector2f(brickset[k].getPosition().x + 10, brickset[k].getPosition().y + 5.0));

				type4++;
				k++;
			}
			else if (vec[i][j] == -1)
			{
				brickset[k].setSize(sf::Vector2f(100.0f, 25.0f));
				brickset[k].setFillColor(sf::Color(244.0, 194.0, 194.0));
				brickset[k].setPosition(sf::Vector2f(-100.0f, -100.0f));

				k++;
			}
	}

	//gameloop
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << evnt.size.width << evnt.size.height << std::endl;
			}
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && paddlePositionX > 0.0)
		{
			if (start == false)
				ballAngle = 60;

			paddlePositionX -= 1.0;
			playerPaddle.move(-1.0f, 0.0f);

			left -= 1.0;
			leftCenter -= 1.0;
			Center -= 1.0;
			rightCenter -= 1.0;
			right -= 1.0;

			start = true;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && paddlePositionX < 900.0)
		{
			if(start == false)
				ballAngle = 120;

			paddlePositionX += 1.0;
			playerPaddle.move(1.0f, 0.0f);

			left += 1.0;
			leftCenter += 1.0;
			Center += 1.0;
			rightCenter += 1.0;
			right += 1.0;

			start = true;
		}

		bool spacepressed = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			Sleep(200);
			while (spacepressed == false) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					spacepressed = true;
					Sleep(200);
				}
			}
		}

		if (start)
		{
			if (ballAngle == 30)
			{
				//x axis
				if (BallX > 988.9)
					movingRightwards = false;
				else if (BallX < 6.1)
					movingRightwards = true;

				if (BallX > 5 && BallX < 990 && movingRightwards == false)
				{
					BallX -= 1.0;
					ball.move(-1.0f, 0.0f);
				}
				else if (BallX > 5 && BallX < 990 && movingRightwards == true)
				{
					BallX += 1.0;
					ball.move(+1.0f, 0.0f);
				}

				//y axis
				if (BallY > 756.1)
					movingUpwards = true;
				else if (BallY < 6.1)
					movingUpwards = false;

				if (BallY > 5 && BallY < 758 && movingUpwards == false)
				{
					BallY += 0.58;
					ball.move(0.0f, +0.58f);
				}
				else if (BallY > 5 && BallY < 758 && movingUpwards == true)
				{
					BallY -= 0.58;
					ball.move(0.0f, -0.58f);
				}
			}

			else if (ballAngle == 60)
			{
				//x axis
				if (BallX > 988.9)
					movingRightwards = false;
				else if (BallX < 6.1)
					movingRightwards = true;

				if (BallX > 5 && BallX < 990 && movingRightwards == false)
				{
					BallX -= 0.58;
					ball.move(-0.58f, 0.0f);
				}
				else if (BallX > 5 && BallX < 990 && movingRightwards == true)
				{
					BallX += 0.58;
					ball.move(+0.58f, 0.0f);
				}

				//y axis
				if (BallY > 756.9)
					movingUpwards = true;
				else if (BallY < 6.1)
					movingUpwards = false;

				if (BallY > 5 && BallY < 758 && movingUpwards == false)
				{
					BallY += 1.0;
					ball.move(0.0f, +1.0f);
				}
				else if (BallY > 5 && BallY < 758 && movingUpwards == true)
				{
					BallY -= 1.0;
					ball.move(0.0f, -1.0f);
				}
			}

			else if (ballAngle == 90)
			{
				//y axis only
				if (BallY > 756.9)
					movingUpwards = true;
				else if (BallY < 6.1)
					movingUpwards = false;

				if (BallY > 5 && BallY < 758 && movingUpwards == false)
				{
					BallY += 1.0;
					ball.move(0.0f, +1.0f);
				}
				else if (BallY > 5 && BallY < 758 && movingUpwards == true)
				{
					BallY -= 1.0;
					ball.move(0.0f, -1.0f);
				}
			}

			else if (ballAngle == 120)
			{
				//x axis
				if (BallX > 988.9)
					movingRightwards = false;
				else if (BallX < 6.1)
					movingRightwards = true;

				if (BallX > 5 && BallX < 990 && movingRightwards == false)
				{
					BallX -= 0.58;
					ball.move(-0.58f, 0.0f);
				}
				else if (BallX > 5 && BallX < 990 && movingRightwards == true)
				{
					BallX += 0.58;
					ball.move(+0.58f, 0.0f);
				}

				//y axis
				if (BallY > 756.9)
					movingUpwards = true;
				else if (BallY < 6.1)
					movingUpwards = false;

				if (BallY > 5 && BallY < 758 && movingUpwards == false)
				{
					BallY += 1.0;
					ball.move(0.0f, +1.0f);
				}
				else if (BallY > 5 && BallY < 758 && movingUpwards == true)
				{
					BallY -= 1.0;
					ball.move(0.0f, -1.0f);
				}
			}

			else if (ballAngle == 150)
			{
				//x axis
				if (BallX > 988.9)
					movingRightwards = false;
				else if (BallX < 6.1)
					movingRightwards = true;

				if (BallX > 5 && BallX < 990 && movingRightwards == false)
				{
					BallX -= 1.0;
					ball.move(-1.0f, 0.0f);
				}
				else if (BallX > 5 && BallX < 990 && movingRightwards == true)
				{
					BallX += 1.0;
					ball.move(+1.0f, 0.0f);
				}

				//y axis
				if (BallY > 756.9)
					movingUpwards = true;
				else if (BallY < 6.1)
					movingUpwards = false;

				if (BallY > 5 && BallY < 758 && movingUpwards == false)
				{
					BallY += 0.58;
					ball.move(0.0f, +0.58f);
				}
				else if (BallY > 5 && BallY < 758 && movingUpwards == true)
				{
					BallY -= 0.58;
					ball.move(0.0f, -0.58f);
				}
			}

			//ball paddle collision
			if (movingUpwards == false && (BallY > 699.6 && BallY < 700.4))
			{
				if (BallX >= left && BallX <= left + 20.0)
				{
					movingUpwards = true;
					movingRightwards = false;
					ballAngle = 30;
				}
				else if (BallX >= leftCenter && BallX <= leftCenter + 20.0)
				{
					ballAngle = 60;
					movingRightwards = false;
					movingUpwards = true;
				}
				else if (BallX >= Center && BallX <= Center + 20.0)
				{
					ballAngle = 90;
					movingUpwards = true;
				}
				else if (BallX >= rightCenter && BallX <= rightCenter + 20.0)
				{
					ballAngle = 120;
					movingRightwards = true;
					movingUpwards = true;
				}
				else if (BallX >= right && BallX <= right + 20.0)
				{
					ballAngle = 150;
					movingRightwards = true;
					movingUpwards = true;
				}
			}

			if (BallY > 750.0)
			{
				lives = lives - 1;
				std::cout << "Life left are: ";
				std::cout << lives;
				std::cout << "\n";

				start = false;

				paddlePositionX = 334;

				BallX = 379.0;
				BallY = 695.0;

				left = 334.0;
				leftCenter = 354.0;
				Center = 374.0;
				rightCenter = 394.0;
				right = 414.0;

				movingUpwards = true;

				playerPaddle.setPosition(sf::Vector2f(334.0f, 700.0f));
				ball.setPosition(sf::Vector2f(374.0f, 680.0f));
			}
		}

		bool scorealreadyadded = false;
		int m = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++)
			{
				if (ball.getGlobalBounds().intersects(brickset[m].getGlobalBounds())) {
					scorealreadyadded = false;

					if (movingUpwards)
						movingUpwards = false;
					else
						movingUpwards = true;

					for (int tri_num = 0; tri_num < type1; tri_num++) {
						if (brickset[m].getGlobalBounds().intersects(triangle[tri_num].getGlobalBounds())) {
							triangle[tri_num].setPosition(sf::Vector2f(-100.0, -100.0));

							//triangle powerup here
							lives = lives - 0.5;
							vec[i][j] = -1;
							scorealreadyadded = true;
						}
					}

					for (int cricle_num = 0; cricle_num < type2; cricle_num++) {
						if (brickset[m].getGlobalBounds().intersects(circle[cricle_num].getGlobalBounds())) {
							circle[cricle_num].setPosition(sf::Vector2f(-100.0, -100.0));

							//circle powerup here
							if (lives < 5) {
								lives = lives + 1;
								scorealreadyadded = true;
							}
							else {
								score = score + 10;
								scorealreadyadded = true;
							}
							vec[i][j] = -1;
						}
					}

					for (int parallelogram_num = 0; parallelogram_num < type3; parallelogram_num++) {
						if (brickset[m].getGlobalBounds().intersects(tri1[parallelogram_num].getGlobalBounds())) {
							tri1[parallelogram_num].setPosition(sf::Vector2f(-100.0, -100.0));
							tri2[parallelogram_num].setPosition(sf::Vector2f(-100.0, -100.0));

							if (m == 0)
							{
								for (int num = 0; num < 10; num++)
								{
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));
								vec[i][j + 1] = -1;
								vec[i + 1][j] = -1;
							}
							else if (m >= 1 && m <= 6)
							{
								for (int num = 0; num < 10; num++)
								{
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i][j + 1] = -1;
								vec[i + 1][j] = -1;
							}
							else if (m == 7)
							{

								for (int num = 0; num < 10; num++)
								{
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i + 1][j] = -1;
							}
							else if (m == 8 || m == 16 || m == 24)
							{

								for (int num = 0; num < 10; num++)
								{
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j + 1] = -1;
								vec[i + 1][j] = -1;
								vec[i - 1][j] = -1;
							}
							else if (m == 15 || m == 23 || m == 31)
							{
								for (int num = 0; num < 10; num++)
								{
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i + 1][j] = -1;
								vec[i - 1][j] = -1;
							}
							else if (m == 32)
							{
								for (int num = 0; num < 10; num++)
								{
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, 0.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, 0.0));

								vec[i][j + 1] = -1;
								vec[i - 1][j] = -1;
							}
							else if (m == 39)
							{

								for (int num = 0; num < 10; num++)
								{
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i - 1][j] = -1;
							}
							else if (m >= 33 && m <= 38)
							{
								for (int num = 0; num < 10; num++)
								{
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i][j + 1] = -1;
								vec[i - 1][j] = -1;
							}
							else
							{

								for (int num = 0; num < 10; num++)
								{
									if (brickset[m + 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(triangle[num].getGlobalBounds()))
										triangle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(circle[num].getGlobalBounds()))
										circle[num].setPosition(sf::Vector2f(-100.0, -100.0));

									if (brickset[m + 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 8].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m + 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}
									if (brickset[m - 1].getGlobalBounds().intersects(tri1[num].getGlobalBounds()))
									{
										tri1[num].setPosition(sf::Vector2f(-100.0, -100.0));
										tri2[num].setPosition(sf::Vector2f(-100.0, -100.0));
									}

									if (brickset[m + 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 8].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m + 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
									if (brickset[m - 1].getGlobalBounds().intersects(innerbrickbrick[num].getGlobalBounds()))
										innerbrickbrick[num].setPosition(sf::Vector2f(-100.0, -100.0));
								}
								brickset[m + 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 1].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m + 8].setPosition(sf::Vector2f(-100.0, -100.0));
								brickset[m - 8].setPosition(sf::Vector2f(-100.0, -100.0));

								vec[i][j - 1] = -1;
								vec[i][j + 1] = -1;
								vec[i + 1][j] = -1;
								vec[i - 1][j] = -1;
							}

							score = score + 10;
							scorealreadyadded = true;
						}
					}

					for (int innerbrickcounter = 0; innerbrickcounter < type4; innerbrickcounter++) {
						if (brickset[m].getGlobalBounds().intersects(innerbrickbrick[innerbrickcounter].getGlobalBounds())) {
							innerbrickbrick[innerbrickcounter].setPosition(sf::Vector2f(-100.0, -100.0));

							//inner brick powerup here
							vec[i][j] = -1;

							score -= 5;
							scorealreadyadded = true;
						}
					}

					if (!scorealreadyadded)
						score = score + 2;

					brickset[m].setPosition(sf::Vector2f(-100.0, -100.0));  //remove the normal brick
					std::cout << "Score is: ";
					std::cout << score;
					std::cout << "\n";

					vec[i][j] = -1;

					//print debug
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 8; j++) {
							cout << vec[i][j] << "  ";
						}
						cout << "\n";
					}

				}
				m++;
			}
		}
		if (score > 9)
			stats[2].setPosition(sf::Vector2f(window.getSize().x - 220, window.getSize().y / (2 + 8) * 2));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			ofstream writer;
			writer.open("savegame.txt");
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 8; j++) {
					writer << vec[i][j] << " ";
				}
				writer << endl;
			}

			writer << lives << " " << score;

			cout << "Game Saved";
			break;
		}

		bool isWin = true;

		for (int i = 0; i < 5 && isWin == true; i++)
		{
			for (int j = 0; j < 8 && isWin == true; j++)
			{
				if (vec[i][j] != -1) {
					isWin = false;
				}

			}
		}

		if (isWin)
			cout << "win";

		sf::Text threeletters[3];

		int i = 0;

		if (isWin == true || lives <= 0)
		{
			ofstream writer;
			writer.open("highscore.txt", ios::app);

			writer << score;
			writer << " :";
			while (true)
			{
				std::stringstream name;
				sf::Text textmain;
				textmain.setFont(font);
				textmain.setString("Enter three letters for your nickname");
				textmain.setCharacterSize(34);
				textmain.setFillColor(sf::Color(244.0, 194.0, 194.0));
				textmain.setPosition(sf::Vector2f(100.0f, 100.0f));
				textmain.setStyle(sf::Text::Bold | sf::Text::Underlined);

				threeletters[0].setFont(font);
				threeletters[0].setCharacterSize(34);
				threeletters[0].setFillColor(sf::Color(244.0, 194.0, 194.0));
				threeletters[0].setPosition(sf::Vector2f(150.0f, 200.0f));
				threeletters[0].setStyle(sf::Text::Bold | sf::Text::Underlined);

				threeletters[1].setFont(font);
				threeletters[1].setCharacterSize(34);
				threeletters[1].setFillColor(sf::Color(244.0, 194.0, 194.0));
				threeletters[1].setPosition(sf::Vector2f(150.0f, 200.0f));
				threeletters[1].setStyle(sf::Text::Bold | sf::Text::Underlined);

				threeletters[2].setFont(font);
				threeletters[2].setCharacterSize(34);
				threeletters[2].setFillColor(sf::Color(244.0, 194.0, 194.0));
				threeletters[2].setPosition(sf::Vector2f(150.0f, 200.0f));
				threeletters[2].setStyle(sf::Text::Bold | sf::Text::Underlined);

				while (i < 3)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
						name << "A";
						writer << "A";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
						name << "B";
						writer << "B";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
						name << "C";
						writer << "C";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
						name << "D";
						writer << "D";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
						name << "E";
						writer << "E";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
						name << "F";
						writer << "F";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
						name << "G";
						writer << "G";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
						name << "H";
						writer << "H";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
						name << "I";
						writer << "I";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
						name << "J";
						writer << "J";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
						name << "K";
						writer << "K";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
						name << "L";
						writer << "L";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
						name << "M";
						writer << "M";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
						name << "N";
						writer << "N";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
						name << "O";
						writer << "O";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
						name << "P";
						writer << "P";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
						name << "Q";
						writer << "Q";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
						name << "R";						writer << "R";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
						name << "S";						writer << "S";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
						name << "T";						writer << "T";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) {
						name << "U";						writer << "U";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
						name << "V";
						writer << "V";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
						name << "W";
						writer << "W";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
						name << "X";
						writer << "X";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
						name << "Y";
						writer << "Y";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
						name << "Z";
						writer << "Z";
						threeletters[i].setString(name.str());
						i++;
						Sleep(300);
					}

					window.clear();
					window.draw(textmain);
					window.draw(threeletters[0]);
					window.draw(threeletters[1]);
					window.draw(threeletters[2]);
					window.display();
					if (i == 3) {
						writer << "\n";
						writer.close();
						window.close();
						return;
					}
				}
			}
		}

		std::stringstream sscore;
		sscore << score;
		std::stringstream slives;
		slives << lives;


		playerPaddle.getGlobalBounds();
		stats[2].setString(sscore.str());
		stats[3].setString(slives.str());

		window.clear();
		window.draw(border);
		window.draw(playerPaddle);
		window.draw(ball);
		for (int i = 0; i < 4; i++)
		{
			window.draw(stats[i]);
		}
		for (int num = 0; num < k; num++)
		{
			window.draw(brickset[num]);
		}
		for (int num = 0; num < 10; num++)
		{
			window.draw(triangle[num]);
			window.draw(circle[num]);
			window.draw(tri1[num]);
			window.draw(tri2[num]);
			window.draw(innerbrickbrick[num]);
		}
		window.display();
	}
}


void vecta(vector<vector<int>>& vec)
{
	bool specialbrick = true, normalbrick = true;
	int special = 0, normal = 0, i, temp;

	srand(time(0));

	for (i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			temp = rand() % 10;

			if (temp > 5 && temp < 9 && specialbrick)
			{
				vec[i][j] = temp;
				special++;
				if (special == 16)
					specialbrick = false;
			}
			else if (temp < 6 && normalbrick)
			{
				vec[i][j] = temp;
				normal++;
				if (normal == 24)
					normalbrick = false;
			}
			else
			{
				j--;
				continue;
			}
			cout << vec[i][j] << "  ";
		}
		cout << "\n";
	}
	for (int j = 0; j < 8; j++)
	{
		temp = rand() % 10;

		if (temp > 5 && specialbrick)
		{
			vec[i][j] = temp;
			special++;
			if (special == 16)
				specialbrick = false;
		}
		else if (temp < 6 && normalbrick)
		{
			vec[i][j] = temp;
			normal++;
			if (normal == 24)
				normalbrick = false;
		}
		else
		{
			j--;
			continue;
		}
		cout << vec[i][j] << "  ";
	}
}

void highscore(sf::RenderWindow& window) {

	string extraction;
	int datascore[100];
	string dataname[100];
	int i = 0;
	ifstream reader;
	reader.open("highscore.txt");
	while (getline(reader, extraction) || i < 100) {     //first line of file is not processed so please donot store score on first line
		reader >> extraction;
		stringstream geek(extraction);
		geek >> datascore[i];
		reader >> extraction;
		dataname[i] = extraction;
		i++;
	}

	int tempnum;
	string tempstring;

	for (int j = 0; j < i; j++)
	{
		for (int k = j + 1; k < i; k++)
		{
			if (datascore[j] < datascore[k])
			{
				tempnum = datascore[j];
				datascore[j] = datascore[k];
				datascore[k] = tempnum;
				tempstring = dataname[j];
				dataname[j] = dataname[k];
				dataname[k] = tempstring;
			}
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Font font;
		font.loadFromFile("Sketch3D.woff");

		sf::Text text;
		sf::Text Score[100];
		sf::Text Name[100];
		text.setFont(font);
		text.setString("LeaderBoard");
		text.setPosition(sf::Vector2f(500.0f, 20.0f));
		text.setCharacterSize(54);
		text.setFillColor(sf::Color(244.0, 194.0, 194.0));
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		sf::Text Sample;
		Sample.setFont(font);
		Sample.setString("Score:Name");
		Sample.setPosition(sf::Vector2f(570.0f, 120.0f));
		Sample.setCharacterSize(34);
		Sample.setFillColor(sf::Color(244.0, 194.0, 194.0));
		Sample.setStyle(sf::Text::Bold | sf::Text::Underlined);

		float offset = 170.0;

		for (int f = 0; datascore[f] > 0 && datascore[f] < 1000; f++)
		{
			Score[f].setFont(font);
			Score[f].setCharacterSize(34);
			Score[f].setFillColor(sf::Color(244.0, 194.0, 194.0));
			Score[f].setStyle(sf::Text::Bold | sf::Text::Underlined);
			std::stringstream sscore;
			sscore << datascore[f];
			Score[f].setString(sscore.str());
			Score[f].setPosition(sf::Vector2f(600.0f, offset));
			offset += 55;
		}
		offset = 170.0;
		for (int f = 0; f < i; f++)
		{
			Name[f].setFont(font);
			Name[f].setCharacterSize(34);
			Name[f].setFillColor(sf::Color(244.0, 194.0, 194.0));
			Name[f].setStyle(sf::Text::Bold | sf::Text::Underlined);
			Name[f].setString(dataname[f]);
			Name[f].setPosition(sf::Vector2f(680.0f, offset));
			offset += 55;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace))
			break;

		window.clear();
		window.draw(text);
		window.draw(Sample);
		for (int f = 0; f < 10; f++)
		{
			window.draw(Name[f]);
			window.draw(Score[f]);
		}
		window.display();
	}
}

void loadgame() {
	ifstream input;
	input.open("savegame.txt");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			input >> vectori[i][j];
		}
	}
	input >> lives;
	input >> score;
	input.close();
}