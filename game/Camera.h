#pragma once

class Camera
{
public:
	Camera(float x, float y);

	void setCenter(float x, float y);

	float getX() const;
	float getY() const;
private:
	float x_;
	float y_;
};