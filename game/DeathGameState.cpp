#include "DeathGameState.h"
#include "Game.h"
#include "EventQueue.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

DeathGameState::DeathGameState(Game &game) :
	GameState(game),
	durationClock_(5.0f)
{
	game_.infoTextUi_.setString("You Died!");
}

void DeathGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Escape)
	{
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::MainMenu));
	}
}

void DeathGameState::update(float deltaTime)
{
	game_.station_.update(deltaTime);
	game_.particlePool_.update(deltaTime);
	game_.bulletPool_.update(deltaTime);
	game_.enemyPool_.update(deltaTime, game_.bulletPool_, game_.particlePool_, game_.player_);

	durationClock_.update(deltaTime);
	if (durationClock_.isDone())
	{
		durationClock_.reset();

		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::MainMenu));
	}
}

void DeathGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(game_.background_);
	target.draw(game_.station_, states);
	target.draw(game_.particlePool_, states);
	target.draw(game_.bulletPool_, states);
	target.draw(game_.enemyPool_, states);

	target.draw(game_.infoTextUi_);
	target.draw(game_.healthUi_);
}