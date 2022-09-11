#include "StarPanel.h"
#include "Rng.h"
#include "TextureData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

StarPanel::StarPanel(uint16_t numStars, float distanceFactor) :
	sf::Drawable(),
	stars_(numStars, Star(0.0f, 0.0f, Config::worldScale * distanceFactor, TextureData::getInstance().getTexture(301))),
	distanceFactor_(distanceFactor)
{
	this->randomize_();
}

void StarPanel::updateFocus(float dX, float dY)
{
	for (Star &star : stars_)
	{
		star.updateOffset(dX * distanceFactor_, dY * distanceFactor_);

		if (star.getWindowX() + star.getWidth() < 0.0f)
		{
			star.setWindowX(star.getWindowX() + Config::windowWidth);
		}
		else if (star.getWindowX() > Config::windowWidth)
		{
			star.setWindowX(star.getWindowX() - Config::windowWidth - star.getWidth());
		}

		if (star.getWindowY() + star.getHeight() < 0.0f)
		{
			star.setWindowY(star.getWindowY() + Config::windowHeight);
		}
		else if (star.getWindowY() > Config::windowHeight)
		{
			star.setWindowY(star.getWindowY() - Config::windowHeight - star.getHeight());
		}
	}
}

void StarPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const Star &star : stars_)
	{
		target.draw(star, states);
	}
}

void StarPanel::randomize_()
{
	const float invWorldScale = 1.0f / Config::worldScale;

	std::mt19937 &eng = Rng::getInstance().getEng();
	std::uniform_real_distribution<float> xDis(0.0f, static_cast<float>(Config::windowWidth));
	std::uniform_real_distribution<float> yDis(0.0f, static_cast<float>(Config::windowHeight));
	std::uniform_int_distribution<uint16_t> textureIdDis(301, 304);

	for (Star &star : stars_)
	{
		star.setWindowX(xDis(eng));
		star.setWindowY(yDis(eng));
		star.setTexture(TextureData::getInstance().getTexture(textureIdDis(eng)));
	}
}