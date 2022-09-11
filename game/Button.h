#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Button : public sf::Drawable
{
public:
	Button(float cX, float cY, const std::string &str, const sf::Texture &texture);

	void updateOnMouseMove(int mouseX, int mouseY);
	void update(float deltaTime);
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isHovered() const;
private:
	enum class State : uint8_t
	{
		None,
		Expand,
		Contract
	};

	State state_;

	sf::Sprite sprite_;
	sf::Text text_;
	float cX_;
	float cY_;
	float velScale_;
	float minScale_;
	float scale_;

	bool isHovered_;
};