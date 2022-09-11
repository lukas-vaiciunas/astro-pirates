#pragma once

class EventQueue;

#include "Listener.h"
#include "DriverState.h"
#include "DriverStateType.h"
#include <SFML/Graphics/Drawable.hpp>

class Driver :
	public Listener,
	public sf::Drawable
{
public:
	Driver();
	~Driver();

	void onEvent(const Event &ev) override;

	void updateOnKeyPress(sf::Keyboard::Key key);
	void updateOnKeyRelease(sf::Keyboard::Key key);
	void updateOnMouseMove(int mouseX, int mouseY);
	void updateOnMousePress(sf::Mouse::Button button);
	void updateOnMouseRelease(sf::Mouse::Button button);
	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isDone() const;
private:
	DriverStateType stateType_;

	DriverState *state_;
	EventQueue &eventQueue_;

	bool isDone_;

	void changeState_(const DriverStateType &stateType);
};