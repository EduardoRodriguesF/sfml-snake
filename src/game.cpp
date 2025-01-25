#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "game.h"

Snake::Snake() {
	direction = Direction::Right;
	head = Node(sf::Vector2f(3.f, 3.f));
}

void Snake::grow() {
	auto ptr = &head;

	while (ptr->next != nullptr) {
		ptr = ptr->next.get();
	}

	ptr->next = std::make_unique<Node>(Node(ptr->value));
}

void Snake::move() {
	sf::Vector2f lastPos = this->head.value;

	switch (this->direction) {
	case Direction::Right:
		head.value.x++;
		break;
	case Direction::Down:
		head.value.y++;
		break;
	case Direction::Left:
		head.value.x--;
		break;
	case Direction::Up:
		head.value.y--;
		break;
	}

	auto ptr = head.next.get();
	while (ptr != nullptr) {
		std::swap(ptr->value, lastPos);
		ptr = ptr->next.get();
	}
}

void Snake::draw(sf::RectangleShape& pixel, sf::RenderWindow& window) {
	auto ptr = &this->head;
	do {
		pixel.setPosition(ptr->value);
		window.draw(pixel);
	} while (ptr = ptr->next.get());
}

Game::Game() {
	pixel.setSize(sf::Vector2f(1.f, 1.f));
	pixel.setFillColor(sf::Color::White);

	this->reset();
}

void Game::reset() {
	this->placeFood();
	this->snake = Snake();
	this->snake.grow();
}

void Game::placeFood() {
	constexpr int WIDTH = 65.f;
	constexpr int HEIGHT = 50.f;

	food = sf::Vector2f(rand() % (WIDTH + 1), rand() % (HEIGHT + 1));
}

Direction opposite(Direction& d) {
	switch (d) {
	case Direction::Right:
		return Direction::Left;
	case Direction::Down:
		return Direction::Up;
	case Direction::Left:
		return Direction::Right;
	case Direction::Up:
		return Direction::Down;
	}
}


void Game::handleInput() {
	if (inputQueue.size() > 4) return;

	Direction input;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		input = Direction::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		input = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		input = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		input = Direction::Up;
	}
	else return;

	// Avoid opposite directions (illegal move)
	if (opposite(snake.direction) == input) return;

	// Avoid repeated input
	if (snake.direction == input || inputQueue.size() > 0 && inputQueue.front() == input) return;

	inputQueue.push(input);
}

void Game::update() {
	if (inputQueue.size() > 0) {
		auto next = inputQueue.front();

		if (opposite(snake.direction) != next) {
			snake.direction = next;
			inputQueue.pop();
		}
	}

	snake.move();

	if (snake.head.value == this->food) {
		snake.grow();
		Game::placeFood();
	}

	auto ptr = &snake.head;
	while (ptr = ptr->next.get()) {
		if (ptr->value == snake.head.value) {
			this->reset();
			break;
		}
	}
}

void Game::draw(sf::RenderWindow& window) {
	snake.draw(pixel, window);

	pixel.setPosition(this->food);
	window.draw(pixel);
}