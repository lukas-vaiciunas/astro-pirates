#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

class InfoTextUi : public sf::Drawable
{
public:
	InfoTextUi();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setString(const std::string &str);
private:
	sf::Text infoText_;
};