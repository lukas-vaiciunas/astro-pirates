#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureData
{
public:
	TextureData(const TextureData &) = delete;
	TextureData &operator=(const TextureData &) = delete;

	static TextureData &getInstance();

	void load(const std::string &filePath);

	const sf::Texture &getTexture(uint16_t id) const;
private:
	std::unordered_map<uint16_t, sf::Texture> textures_;

	TextureData();
	~TextureData() {}
};