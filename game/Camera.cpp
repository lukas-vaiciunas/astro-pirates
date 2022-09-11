#include "Camera.h"
#include "Config.h"

Camera::Camera(float x, float y) :
	x_(x),
	y_(y)
{}

void Camera::setCenter(float x, float y)
{
	const float invWorldScale = 1.0f / Config::worldScale;

	x_ = x - Config::windowWidth * 0.5f * invWorldScale;
	y_ = y - Config::windowHeight * 0.5f * invWorldScale;
}

float Camera::getX() const
{
	return x_;
}

float Camera::getY() const
{
	return y_;
}