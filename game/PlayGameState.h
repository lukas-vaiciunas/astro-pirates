#pragma once

#include "GameState.h"

class PlayGameState : public GameState
{
public:
	PlayGameState(Game &game);

	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};