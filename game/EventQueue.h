#pragma once

class Event;
class Listener;

#include <queue>
#include <unordered_set>

class EventQueue
{
public:
	EventQueue(const EventQueue &) = delete;
	EventQueue &operator=(const EventQueue &) = delete;

	static EventQueue &getInstance();

	void dispatch();
	void send(Event *ev);

	void addListener(Listener *listener);
	void removeListener(Listener *listener);
private:
	std::queue<Event *> evQueue_;
	std::unordered_set<Listener *> listeners_;

	EventQueue();
	~EventQueue();
};