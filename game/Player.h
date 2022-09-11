#pragma once

class BulletPool;

#include "DestructibleEntity.h"
#include "DurationClock.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class Player : public DestructibleEntity
{
public:
	Player(
		float x, float y,
		float speed,
		float maxHealth,
		float shootingCooldownSecs,
		const sf::Texture &texture);

	void updateOnKeyPress(sf::Keyboard::Key key);
	void updateOnKeyRelease(sf::Keyboard::Key key);
	void updateOnMouseMove(int mouseX, int mouseY, float cameraX, float cameraY);
	void updateOnMousePress(sf::Mouse::Button button);
	void updateOnMouseRelease(sf::Mouse::Button button);
	void update(
		float deltaTime,
		float cameraX, float cameraY,
		BulletPool &bulletPool,
		ParticlePool &particlePool);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	DurationClock shootingCooldownClock_;

	float speed_;

	float windowTargetX_;
	float windowTargetY_;

	float angleRad_;
	float angleDeg_;

	bool isMovingUp_;
	bool isMovingDown_;
	bool isMovingLeft_;
	bool isMovingRight_;

	bool isShooting_;

	void updateAngle_(float cameraX, float cameraY);
	void updateShooting_(float deltaTime, BulletPool &bulletPool);
};