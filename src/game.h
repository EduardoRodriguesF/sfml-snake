#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Snake.h"

class Game {
public:
	Game();
	void handleInput();
	void loop(sf::RenderWindow& window);
	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::Clock clock;
	std::queue<Direction> inputQueue;

	Snake snake;
	sf::Vector2f food;
	sf::RectangleShape pixel;
	float speed;

	void placeFood();
	void reset();
};