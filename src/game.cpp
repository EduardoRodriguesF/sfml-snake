#include <SFML/Graphics.hpp>
#include <queue>
#include "game.h"
#include "Snake.h"

Game::Game() {
	pixel.setSize(sf::Vector2f(1.f, 1.f));
	pixel.setFillColor(sf::Color::White);

	this->reset();
}

void Game::reset() {
    srand(time(0));

	this->placeFood();
	this->snake = Snake();
	this->snake.grow();
	this->speed = 10.f;
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

void Game::loop(sf::RenderWindow& window) {
    sf::Time accumulator;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        this->handleInput();

		sf::Time elapsed = clock.restart();
		accumulator += elapsed;

		while (accumulator.asSeconds() >= 1.f / this->speed) {
			this->update();
			accumulator -= sf::seconds(1.f / this->speed);
		}

        window.clear();
        this->draw(window);
        window.display();
    }
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
		this->speed += 0.5f;
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