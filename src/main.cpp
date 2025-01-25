#include <SFML/Graphics.hpp>
#include "game.h"

const sf::View view(sf::FloatRect({ 0.f, 0.f }, { 65.f, 50.f }));
constexpr sf::Time FRAME_RATE = sf::seconds(1.0f);

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({780u, 600u}), "Snake");
    window.setFramerateLimit(144);
    window.setView(view);

    Game game;

    game.loop(window);
}
