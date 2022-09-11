#pragma once

#include "DriverState.h"
#include "PulsatingText.h"
#include "Button.h"
#include "Background.h"

class MainMenu : public DriverState
{
public:
	MainMenu();

	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	PulsatingText titleText_;

	Button playButton_;
	Button quitButton_;

	Background background_;
	float backgroundScrollSpeed_;
	float backgroundX_;
	float backgroundY_;
};