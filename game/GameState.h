#pragma once

class Game;

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class GameState : public sf::Drawable
{
public:
	GameState(Game &game);
	virtual ~GameState() {}

	virtual void updateOnKeyPress(sf::Keyboard::Key key) {};
	virtual void updateOnKeyRelease(sf::Keyboard::Key key) {};
	virtual void updateOnMouseMove(int mouseX, int mouseY) {};
	virtual void updateOnMousePress(sf::Mouse::Button button) {};
	virtual void updateOnMouseRelease(sf::Mouse::Button button) {};
	virtual void update(float deltaTime) {};

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
protected:
	Game &game_;
};