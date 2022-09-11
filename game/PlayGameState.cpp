#include "PlayGameState.h"
#include "Game.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayGameState::PlayGameState(Game &game) :
	GameState(game)
{}

void PlayGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Escape)
	{
		game_.changeState_(Game::StateType::Paused);
	}
	else game_.player_.updateOnKeyPress(key);
}

void PlayGameState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	game_.player_.updateOnKeyRelease(key);
}

void PlayGameState::updateOnMouseMove(int mouseX, int mouseY)
{
	game_.player_.updateOnMouseMove(mouseX, mouseY, game_.camera_.getX(), game_.camera_.getY());
}

void PlayGameState::updateOnMousePress(sf::Mouse::Button button)
{
	game_.player_.updateOnMousePress(button);
}

void PlayGameState::updateOnMouseRelease(sf::Mouse::Button button)
{
	game_.player_.updateOnMouseRelease(button);
}

void PlayGameState::update(float deltaTime)
{
	game_.station_.update(deltaTime);
	game_.particlePool_.update(deltaTime);
	game_.bulletPool_.update(deltaTime);
	game_.enemyPool_.update(deltaTime, game_.bulletPool_, game_.particlePool_, game_.player_);
	game_.player_.update(deltaTime, game_.camera_.getX(), game_.camera_.getY(), game_.bulletPool_, game_.particlePool_);

	if (game_.level_.existsObjective())
	{
		game_.targetArrowUi_.update(
			game_.player_.getX() + game_.player_.getWidth() * 0.5f,
			game_.player_.getY() + game_.player_.getHeight() * 0.5f);
	}

	game_.updateCameraPosition_();
}

void PlayGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(game_.background_);
	target.draw(game_.station_, states);
	target.draw(game_.particlePool_, states);
	target.draw(game_.bulletPool_, states);
	target.draw(game_.enemyPool_, states);
	target.draw(game_.player_, states);

	if (game_.level_.existsObjective())
	{
		target.draw(game_.targetArrowUi_);
		target.draw(game_.infoTextUi_);
	}

	target.draw(game_.healthUi_);
}