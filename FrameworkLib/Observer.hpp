#pragma once

#include <map>
#include <vector>
#include <utility>

// Implementation:
// https://juanchopanzacpp.wordpress.com/2013/02/24/simple-observer-pattern-implementation-c11/

namespace framework
{

enum class Event 
{ 
	KeyDown, 
	KeyUp, 
	Word 
};

class GameEvent
{
	std::string	name;
	size_t id;
};

class Observer;

class Subject
{
public:
	void addObserver(const Event& event, Observer& observer)
	{
		observers[event].push_back(observer);
	}

	void notify(const Event& event)
	{
		for (const auto& obs : observers[event])
		{
			obs.notification();
		}
	}

private:
	std::map<Event, std::vector<Observer&> > observers;
};


class Observer
{
public:
	void notification() const {};

};

} // framework