#include "Player.h"
#include "BulletPool.h"
#include "EventQueue.h"
#include "Event.h"
#include "TextureData.h"
#include "AudioData.h"
#include "Constants.h"
#include "Config.h"

Player::Player(
	float x, float y,
	float speed,
	float maxHealth,
	float shootingCooldownSecs,
	const sf::Texture &texture)
	:
	DestructibleEntity(x, y, maxHealth, texture),
	shootingCooldownClock_(shootingCooldownSecs),
	speed_(speed),
	windowTargetX_(0.0f),
	windowTargetY_(0.0f),
	angleRad_(0.0f),
	angleDeg_(0.0f),
	isMovingUp_(false),
	isMovingDown_(false),
	isMovingLeft_(false),
	isMovingRight_(false),
	isShooting_(false)
{
	shootingCooldownClock_.rig();
}

void Player::updateOnKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = true;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = true;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = true;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = true;
			break;
	}
}

void Player::updateOnKeyRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = false;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = false;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = false;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = false;
			break;
	}
}

void Player::updateOnMouseMove(int mouseX, int mouseY, float cameraX, float cameraY)
{
	float invWorldScale = 1.0f / Config::worldScale;

	windowTargetX_ = mouseX * invWorldScale;
	windowTargetY_ = mouseY * invWorldScale;
}

void Player::update(
	float deltaTime,
	float cameraX, float cameraY,
	BulletPool &bulletPool,
	ParticlePool &particlePool)
{
	float velX = 0.0f;
	float velY = 0.0f;

	if (isMovingUp_)
	{
		velY -= speed_;
	}
	if (isMovingDown_)
	{
		velY += speed_;
	}
	if (isMovingLeft_)
	{
		velX -= speed_;
	}
	if (isMovingRight_)
	{
		velX += speed_;
	}

	float sqCurrSpeed = velX * velX + velY * velY;

	if (sqCurrSpeed > speed_ * speed_)
	{
		float fixRatio = speed_ / sqrt(sqCurrSpeed);

		velX *= fixRatio;
		velY *= fixRatio;
	}

	x_ += velX * deltaTime;
	y_ += velY * deltaTime;

	sprite_.setPosition(x_, y_);

	this->updateAngle_(cameraX, cameraY);
	this->updateShooting_(deltaTime, bulletPool);
	if (this->updateBulletCollisions_(bulletPool, particlePool, true))
	{
		EventQueue::getInstance().send(new EventPlayerHurt(health_ / maxHealth_));
	}

	if (!this->isLive())
	{
		EventQueue::getInstance().send(new EventPlayerDeath());
	}
}

void Player::updateOnMousePress(sf::Mouse::Button button)
{
	isShooting_ = true;
}

void Player::updateOnMouseRelease(sf::Mouse::Button button)
{
	isShooting_ = false;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(angleDeg_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);
	
	Entity::draw(target, states);
}

void Player::updateAngle_(float cameraX, float cameraY)
{
	float dX = (windowTargetX_ + cameraX) - (x_ + width_ * 0.5f);
	float dY = (windowTargetY_ + cameraY) - (y_ + height_ * 0.5f);

	angleRad_ = atan2f(dY, dX);
	angleDeg_ = angleRad_ * 180.0f / Constants::pi;
}

void Player::updateShooting_(float deltaTime, BulletPool &bulletPool)
{
	shootingCooldownClock_.update(deltaTime);

	if (isShooting_ && shootingCooldownClock_.isDone())
	{
		shootingCooldownClock_.reset();

		if (!bulletPool.isFull())
		{
			bulletPool.add(
				new Bullet(
					x_ + width_ * 0.5f, y_ + height_ * 0.5f,
					128.0f * cosf(angleRad_), 128.0f * sinf(angleRad_),
					25.0f,
					2.0f,
					true,
					TextureData::getInstance().getTexture(101)));

			AudioData::getInstance().playSound(3);
		}
	}
}