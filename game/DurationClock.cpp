#include "DurationClock.h"

DurationClock::DurationClock(float targetSecs) :
	targetSecs_(targetSecs),
	currSecs_(0.0f)
{}

void DurationClock::update(float elapsedSecs)
{
	currSecs_ += elapsedSecs;
}

void DurationClock::reset()
{
	currSecs_ = 0.0f;
}

void DurationClock::rig()
{
	currSecs_ = targetSecs_;
}

bool DurationClock::isDone() const
{
	return currSecs_ >= targetSecs_;
}

float DurationClock::getTargetSecs() const
{
	return targetSecs_;
}

float DurationClock::getCurrSecs() const
{
	return currSecs_;
}