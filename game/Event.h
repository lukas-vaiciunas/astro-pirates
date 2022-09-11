#pragma once

#include "EventType.h"
#include "DriverStateType.h"

class Event
{
public:
	Event(const EventType &type) :
		type_(type)
	{}
	virtual ~Event() {}

	const EventType &getType() const
	{
		return type_;
	}
private:
	EventType type_;
};

class EventChangeDriverState : public Event
{
public:
	EventChangeDriverState(const DriverStateType &driverStateType) :
		Event(EventType::ChangeDriverState),
		driverStateType_(driverStateType)
	{}

	const DriverStateType &getDriverStateType() const
	{
		return driverStateType_;
	}
private:
	DriverStateType driverStateType_;
};

class EventExit : public Event
{
public:
	EventExit() :
		Event(EventType::Exit)
	{}
};

class EventTargetDestroyed : public Event
{
public:
	EventTargetDestroyed(uint16_t id) :
		Event(EventType::TargetDestroyed),
		id_(id)
	{}

	uint16_t getId() const
	{
		return id_;
	}
private:
	uint16_t id_;
};

class EventUpdateObjectiveUi : public Event
{
public:
	EventUpdateObjectiveUi() :
		Event(EventType::UpdateObjectiveUi)
	{}
};

class EventPlayerHurt : public Event
{
public:
	EventPlayerHurt(float healthRatio) :
		Event(EventType::PlayerHurt),
		healthRatio_(healthRatio)
	{}

	float getHealthRatio() const
	{
		return healthRatio_;
	}
private:
	float healthRatio_;
};

class EventPlayerDeath : public Event
{
public:
	EventPlayerDeath() :
		Event(EventType::PlayerDeath)
	{}
};