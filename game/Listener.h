#pragma once

class Event;

#include "EventType.h"
#include <unordered_set>

class Listener
{
public:
	Listener(const std::unordered_set<EventType> &acceptedEventTypeSet);
	virtual ~Listener();

	virtual void onEvent(const Event &ev) = 0;

	bool acceptsEventType(const EventType &eventType) const;
private:
	const std::unordered_set<EventType> acceptedEventTypeSet_;
};