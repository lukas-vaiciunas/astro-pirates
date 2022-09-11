#include "PausedGameState.h"
#include "Game.h"
#include "EventQueue.h"
#include "Event.h"
#include "TextureData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

PausedGameState::PausedGameState(Game &game) :
	GameState(game),
	titleText_(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f, 0.5f, 0.75f, "PAUSED"),
	resumeButton_(
		Config::windowWidth * 0.5f,
		Config::windowHeight * 0.5f,
		"RESUME",
		TextureData::getInstance().getTexture(602)),
	quitButton_(
		Config::windowWidth * 0.5f,
		Config::windowHeight * 0.75f,
		"QUIT",
		TextureData::getInstance().getTexture(602)),
	overlay_()
{
	overlay_.setPosition(0.0f, 0.0f);
	overlay_.setSize(sf::Vector2f(static_cast<float>(Config::windowWidth), static_cast<float>(Config::windowHeight)));
	overlay_.setFillColor(sf::Color(8, 8, 8, 175));
}

void PausedGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Escape)
	{
		game_.changeState_(Game::StateType::Play);
	}
}

void PausedGameState::updateOnMouseMove(int mouseX, int mouseY)
{
	resumeButton_.updateOnMouseMove(mouseX, mouseY);
	quitButton_.updateOnMouseMove(mouseX, mouseY);
}

void PausedGameState::updateOnMousePress(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		if (resumeButton_.isHovered())
		{
			game_.changeState_(Game::StateType::Play);
		}
		else if (quitButton_.isHovered())
		{
			EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::MainMenu));
		}
	}
}

void PausedGameState::update(float deltaTime)
{
	titleText_.update(deltaTime);
}

void PausedGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(game_.background_);
	target.draw(game_.station_, states);
	target.draw(game_.particlePool_, states);
	target.draw(game_.bulletPool_, states);
	target.draw(game_.enemyPool_, states);
	target.draw(game_.player_, states);

	target.draw(overlay_);
	target.draw(titleText_);
	target.draw(resumeButton_);
	target.draw(quitButton_);
}