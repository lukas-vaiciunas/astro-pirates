#include "Game.h"
#include "PlayGameState.h"
#include "PausedGameState.h"
#include "DeathGameState.h"
#include "Event.h"
#include "AudioData.h"
#include "TextureData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Game::Game() :
	DriverState(),
	Listener({ EventType::UpdateObjectiveUi, EventType::PlayerHurt, EventType::PlayerDeath }),
	stateType_(StateType::None),
	state_(nullptr),
	player_(0.0f, 0.0f, 32.0f, 100.0f, 0.25f, TextureData::getInstance().getTexture(1)),
	enemyPool_(150),
	bulletPool_(500),
	particlePool_(500),
	camera_(0.0f, 0.0f),
	background_(),
	station_(32.0f, 32.0f, 1.0f, TextureData::getInstance().getTexture(201)),
	level_(player_, enemyPool_),
	healthUi_(Config::windowWidth * 0.1f, Config::windowHeight * 0.9f, 5),
	targetArrowUi_(
		(Config::windowWidth + Config::windowHeight) * 0.5f * 0.1f,
		TextureData::getInstance().getTexture(601)),
	infoTextUi_()
{
	this->updateCameraPosition_();
	this->changeState_(StateType::Play);

	AudioData::getInstance().playMusic(1);
}

Game::~Game()
{
	delete state_;
}

void Game::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::UpdateObjectiveUi)
	{
		targetArrowUi_.setTargetX(level_.getObjectiveX());
		targetArrowUi_.setTargetY(level_.getObjectiveY());

		infoTextUi_.setString("Objective: Eliminate the Alien Pirates!");
	}
	else if (ev.getType() == EventType::PlayerHurt)
	{
		healthUi_.update(static_cast<const EventPlayerHurt &>(ev).getHealthRatio());
	}
	else if (ev.getType() == EventType::PlayerDeath)
	{
		particlePool_.spawnExplosion(
			player_.getX() + player_.getWidth() * 0.5f,
			player_.getY() + player_.getHeight() * 0.5f,
			40);

		if (!particlePool_.isFull())
		{
			particlePool_.add(
				new Particle(
					player_.getX() + player_.getWidth() * 0.5f,
					player_.getY() + player_.getHeight() * 0.5f,
					0.0f, 0.0f,
					30.0f,
					5.0f,
					TextureData::getInstance().getTexture(502)));
		}

		AudioData::getInstance().playSound(5);

		this->changeState_(StateType::Death);
	}
}

void Game::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Game::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Game::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Game::updateOnMousePress(sf::Mouse::Button button)
{
	state_->updateOnMousePress(button);
}

void Game::updateOnMouseRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseRelease(button);
}

void Game::update(float deltaTime)
{
	state_->update(deltaTime);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::worldScale, Config::worldScale);
	states.transform.translate(-camera_.getX(), -camera_.getY());

	target.draw(*state_, states);
}

void Game::updateCameraPosition_()
{
	const float invWorldScale = 1.0f / Config::worldScale;

	camera_.setCenter(
		player_.getX() + player_.getWidth() * 0.5f,
		player_.getY() + player_.getHeight() * 0.5f);

	background_.setFocus(
		camera_.getX() + Config::windowWidth * 0.5f * invWorldScale,
		camera_.getY() + Config::windowHeight * 0.5f * invWorldScale);
}

void Game::changeState_(const StateType &stateType)
{
	if (stateType_ == stateType)
		return;

	stateType_ = stateType;
	delete state_;

	switch (stateType_)
	{
		case StateType::Play:
			state_ = new PlayGameState(*this);
			break;
		case StateType::Paused:
			state_ = new PausedGameState(*this);
			break;
		case StateType::Death:
			state_ = new DeathGameState(*this);
			break;
	}
}