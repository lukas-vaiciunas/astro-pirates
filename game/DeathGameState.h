#pragma once

#include "GameState.h"
#include "DurationClock.h"

class DeathGameState : public GameState
{
public:
	DeathGameState(Game &game);

	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	DurationClock durationClock_;
};