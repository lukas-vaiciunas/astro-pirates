#include "Driver.h"
#include "TextureData.h"
#include "Config.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void setupConfig();

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //

	const sf::Color clearColor(8, 8, 8);

	setupConfig();

	sf::RenderWindow window(
		sf::VideoMode(Config::windowWidth, Config::windowHeight, Config::windowBitsPerPixel),
		"Astro-Pirates",
		sf::Style::Fullscreen);

	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	TextureData::getInstance().load("data/textures.txt");

	Driver driver;

	sf::Clock gameClock;
	float deltaTime = gameClock.restart().asSeconds();

	while (window.isOpen() && !driver.isDone())
	{
		deltaTime = gameClock.restart().asSeconds();

		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::MouseMoved)
			{
				driver.updateOnMouseMove(ev.mouseMove.x, ev.mouseMove.y);
			}
			else if (ev.type == sf::Event::MouseButtonPressed)
			{
				driver.updateOnMousePress(ev.mouseButton.button);
			}
			else if (ev.type == sf::Event::MouseButtonReleased)
			{
				driver.updateOnMouseRelease(ev.mouseButton.button);
			}
			else if (ev.type == sf::Event::KeyPressed)
			{
				driver.updateOnKeyPress(ev.key.code);
			}
			else if (ev.type == sf::Event::KeyReleased)
			{
				driver.updateOnKeyRelease(ev.key.code);
			}
			else if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		driver.update(deltaTime);
		
		window.clear(clearColor);
		window.draw(driver);
		window.display();
	}

	return 0;
}

void setupConfig()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	Config::windowWidth = videoMode.width;
	Config::windowHeight = videoMode.height;
	Config::windowBitsPerPixel = videoMode.bitsPerPixel;

	Config::worldScale = (Config::windowWidth + Config::windowHeight) * 0.5f * 0.004f;

	Config::largeTextSize_ = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.5f * 0.128);
	Config::mediumTextSize_ = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.5f * 0.064);
	Config::smallTextSize_ = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.5f * 0.032);
}