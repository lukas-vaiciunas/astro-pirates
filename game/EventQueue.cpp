#include "EventQueue.h"
#include "Event.h"
#include "Listener.h"

EventQueue::EventQueue() :
	evQueue_(),
	listeners_()
{}

EventQueue::~EventQueue()
{
	while (!evQueue_.empty())
	{
		delete evQueue_.front();
		evQueue_.pop();
	}
}

EventQueue &EventQueue::getInstance()
{
	static EventQueue instance;
	return instance;
}

void EventQueue::dispatch()
{
	while (!evQueue_.empty())
	{
		Event *ev = evQueue_.front();
		evQueue_.pop();

		for (auto it = listeners_.cbegin(); it != listeners_.cend(); ++it)
		{
			if ((*it)->acceptsEventType(ev->getType()))
			{
				(*it)->onEvent(*ev);
			}
		}

		delete ev;
	}
}

void EventQueue::send(Event *ev)
{
	evQueue_.push(ev);
}

void EventQueue::addListener(Listener *listener)
{
	listeners_.emplace(listener);
}

void EventQueue::removeListener(Listener *listener)
{
	listeners_.erase(listener);
}