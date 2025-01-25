#include "Snake.h"

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
