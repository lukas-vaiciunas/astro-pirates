#include "Driver.h"
#include "EventQueue.h"
#include "MainMenu.h"
#include "Game.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

Driver::Driver() :
	Listener({ EventType::ChangeDriverState, EventType::Exit }),
	sf::Drawable(),
	stateType_(DriverStateType::None),
	state_(nullptr),
	eventQueue_(EventQueue::getInstance()),
	isDone_(false)
{
	this->changeState_(DriverStateType::MainMenu);
}

Driver::~Driver()
{
	this->changeState_(DriverStateType::None);
}

void Driver::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::ChangeDriverState)
	{
		this->changeState_(static_cast<const EventChangeDriverState &>(ev).getDriverStateType());
	}
	else if (ev.getType() == EventType::Exit)
	{
		isDone_ = true;
	}
}

void Driver::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Driver::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Driver::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Driver::updateOnMousePress(sf::Mouse::Button button)
{
	state_->updateOnMousePress(button);
}

void Driver::updateOnMouseRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseRelease(button);
}

void Driver::update(float deltaTime)
{
	eventQueue_.dispatch();

	state_->update(deltaTime);
}

void Driver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

bool Driver::isDone() const
{
	return isDone_;
}

void Driver::changeState_(const DriverStateType &stateType)
{
	if (stateType_ == stateType)
		return;

	stateType_ = stateType;
	delete state_;

	switch (stateType_)
	{
		case DriverStateType::MainMenu:
			state_ = new MainMenu();
			break;
		case DriverStateType::Game:
			state_ = new Game();
			break;
	}
}