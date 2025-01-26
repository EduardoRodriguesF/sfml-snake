#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Snake.h"

constexpr float INITIAL_SPEED = 10.f;

enum class GameState {
    Playing,
    LoseSequence,
    GameOver,
};

class Game {
public:
	Game();
	void handleInput();
	void loop(sf::RenderWindow& window);
	void update();
	void draw(sf::RenderWindow& window);

private:
    GameState state;
	sf::Clock clock;
	std::queue<Direction> inputQueue;

	Snake snake;
	sf::Vector2f food;
	sf::RectangleShape pixel;
	float speed;

	void placeFood();
	void reset();

    void changeState(GameState state);
    void update_loseSequence();
    void update_gameOver();
};
