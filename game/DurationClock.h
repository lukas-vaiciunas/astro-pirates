#pragma once

class DurationClock
{
public:
	DurationClock(float targetSecs);

	void update(float elapsedSecs);

	void reset();
	void rig();

	bool isDone() const;
	float getTargetSecs() const;
	float getCurrSecs() const;
private:
	float targetSecs_;
	float currSecs_;
};