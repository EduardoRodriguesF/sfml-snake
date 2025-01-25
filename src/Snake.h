#pragma once
#include <SFML/Graphics.hpp>

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