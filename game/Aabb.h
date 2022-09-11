#pragma once

class Aabb
{
public:
	Aabb(float x, float y, float width, float height);
	virtual ~Aabb() {}

	bool isCollidingWith(const Aabb &other) const;
	bool contains(float x, float y) const;

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
protected:
	float x_;
	float y_;
	float width_;
	float height_;
};