#include "InfoTextUi.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

InfoTextUi::InfoTextUi() :
	sf::Drawable(),
	infoText_()
{
	infoText_.setFont(FontData::getInstance().getFont());
	infoText_.setCharacterSize(Config::smallTextSize_);
	infoText_.setOutlineThickness(Config::worldScale * 0.5f);
	infoText_.setOutlineColor(sf::Color(220, 220, 220));
	infoText_.setFillColor(sf::Color(8, 8, 8));
	infoText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.1f);
}

void InfoTextUi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(infoText_, states);
}

void InfoTextUi::setString(const std::string &str)
{
	infoText_.setString(str);

	infoText_.setOrigin(
		infoText_.getLocalBounds().left + infoText_.getLocalBounds().width * 0.5f,
		infoText_.getLocalBounds().top + infoText_.getLocalBounds().height * 0.5f);
}