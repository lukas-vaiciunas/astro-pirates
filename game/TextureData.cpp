#include "TextureData.h"
#include <fstream>

TextureData::TextureData() :
	textures_()
{}

TextureData &TextureData::getInstance()
{
	static TextureData instance;
	return instance;
}

void TextureData::load(const std::string &filePath)
{
	std::ifstream in(filePath, std::ios_base::in);
	if (!in.is_open())
	{
		printf("Failed to open file \"%s\" in TextureData!\n", filePath.c_str());
		return;
	}

	textures_.clear();

	uint16_t numTextures;
	in >> numTextures;

	for(uint16_t i = 0; i < numTextures; ++i)
	{
		uint16_t id;
		std::string texturePath;

		in >> id >> texturePath;

		sf::Texture texture;
		texture.loadFromFile(texturePath);

		textures_.emplace(id, std::move(texture));
	}

	in.close();
}

const sf::Texture &TextureData::getTexture(uint16_t id) const
{
	return textures_.find(id)->second;
}