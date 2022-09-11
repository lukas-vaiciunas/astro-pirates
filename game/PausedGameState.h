#pragma once

#include "GameState.h"
#include "PulsatingText.h"
#include "Button.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PausedGameState : public GameState
{
public:
	PausedGameState(Game &game);

	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	PulsatingText titleText_;
	Button resumeButton_;
	Button quitButton_;
	sf::RectangleShape overlay_;
};