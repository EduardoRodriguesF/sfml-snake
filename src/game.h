#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

enum class Direction {
	Right = 0,
	Down,
	Left,
	Up,
};

class Snake {
public:
	class Node {
	public:
		Node() : value(sf::Vector2f(0.f, 0.f)) {}
		Node(sf::Vector2f vec) : value(vec) {}

		sf::Vector2f value;
		std::unique_ptr<Node> next;
	};

	Direction direction;
	Node head;

	Snake();
	void move();
	void grow();
	void draw(sf::RectangleShape& pixel, sf::RenderWindow& window);
};

class Game {
public:
	Game();
	void handleInput();
	void update();
	void draw(sf::RenderWindow&);

private:
	Snake snake;
	sf::Vector2f food;
	sf::RectangleShape pixel;
	std::queue<Direction> inputQueue;

	void placeFood();
	void reset();
};