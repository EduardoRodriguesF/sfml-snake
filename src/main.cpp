#include <SFML/Graphics.hpp>
#include "game.h"

const sf::View view(sf::FloatRect({ 0.f, 0.f }, { 65.f, 50.f }));
constexpr sf::Time FRAME_RATE = sf::seconds(1.0f);

int main()
{
    sf::Clock clock;
    sf::Time accumulator;
    float gameSpeed = 10.f;

    srand(time(0));

    auto window = sf::RenderWindow(sf::VideoMode({780u, 600u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setView(view);

    Game game;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        game.handleInput();

        sf::Time elapsed = clock.restart();
        accumulator += elapsed;

        while (accumulator.asSeconds() >= 1.f / gameSpeed) {
            game.update();
            accumulator -= sf::seconds(1.f / gameSpeed);
        }

        window.clear();
        game.draw(window);
        window.display();
    }
}
