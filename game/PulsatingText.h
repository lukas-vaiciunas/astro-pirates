#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

class PulsatingText : public sf::Drawable
{
public:
	PulsatingText(
		float cX, float cY,
		float velScale,
		float minScale,
		const std::string &str);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	enum class State : uint8_t
	{
		Expand,
		Contract
	};

	State state_;

	sf::Text text_;
	float cX_;
	float cY_;
	float velScale_;
	float minScale_;
	float scale_;
};