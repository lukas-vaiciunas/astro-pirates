#include "Aabb.h"

Aabb::Aabb(float x, float y, float width, float height) :
	x_(x),
	y_(y),
	width_(width),
	height_(height)
{}

bool Aabb::isCollidingWith(const Aabb &other) const
{
	return x_ < other.x_ + other.width_
		&& x_ + width_ > other.x_
		&& y_ < other.y_ + other.height_
		&& y_ + height_ > other.y_;
}

bool Aabb::contains(float x, float y) const
{
	return x > x_
		&& x < x_ + width_
		&& y > y_
		&& y < y_ + height_;
}

float Aabb::getX() const
{
	return x_;

}

float Aabb::getY() const
{
	return y_;
}

float Aabb::getWidth() const
{
	return width_;
}

float Aabb::getHeight() const
{
	return height_;
}