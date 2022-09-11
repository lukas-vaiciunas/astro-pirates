#include "Enemy.h"

Enemy::Enemy(uint16_t id, float x, float y, float maxHealth, const sf::Texture &texture) :
	DestructibleEntity(x, y, maxHealth, texture),
	Identifiable(id)
{}