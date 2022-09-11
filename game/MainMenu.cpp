#include "MainMenu.h"
#include "TextureData.h"
#include "Config.h"
#include "EventQueue.h"
#include "Event.h"
#include "AudioData.h"
#include <SFML/Graphics/RenderTarget.hpp>

MainMenu::MainMenu() :
	DriverState(),
	titleText_(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f, 0.5f, 0.75f, "ASTRO-PIRATES"),
	playButton_(
		Config::windowWidth * 0.5f, Config::windowHeight * 0.5f,
		"PLAY",
		TextureData::getInstance().getTexture(602)),
	quitButton_(
		Config::windowWidth * 0.5f, Config::windowHeight * 0.75f,
		"QUIT",
		TextureData::getInstance().getTexture(602)),
	background_(),
	backgroundScrollSpeed_(64.0f),
	backgroundX_(0.0f),
	backgroundY_(0.0f)
{
	AudioData::getInstance().playMusic(2);
}

void MainMenu::updateOnMouseMove(int mouseX, int mouseY)
{
	playButton_.updateOnMouseMove(mouseX, mouseY);
	quitButton_.updateOnMouseMove(mouseX, mouseY);
}

void MainMenu::updateOnMousePress(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		if (playButton_.isHovered())
		{
			EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Game));
		}
		else if (quitButton_.isHovered())
		{
			EventQueue::getInstance().send(new EventExit());
		}
	}
}

void MainMenu::update(float deltaTime)
{
	titleText_.update(deltaTime);
	playButton_.update(deltaTime);
	quitButton_.update(deltaTime);

	backgroundY_ -= backgroundScrollSpeed_ * deltaTime;
	background_.setFocus(backgroundX_, backgroundY_);
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(background_, states);
	target.draw(titleText_, states);
	target.draw(playButton_, states);
	target.draw(quitButton_, states);
}