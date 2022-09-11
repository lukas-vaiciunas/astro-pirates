#include "Listener.h"
#include "EventQueue.h"

Listener::Listener(const std::unordered_set<EventType> &acceptedEventTypeSet) :
	acceptedEventTypeSet_(acceptedEventTypeSet)
{
	EventQueue::getInstance().addListener(this);
}

Listener::~Listener()
{
	EventQueue::getInstance().removeListener(this);
}

bool Listener::acceptsEventType(const EventType &eventType) const
{
	return acceptedEventTypeSet_.find(eventType) != acceptedEventTypeSet_.cend();
}