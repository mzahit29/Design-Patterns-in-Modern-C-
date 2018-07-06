#pragma once
#include "stdafx.h"
#include <vector>

template <typename> class Observer;  // Forward decl

template <typename T>
class Observable
{
	std::vector<Observer<T>*> observers;
public:
	void notify(T& source, const string & field_name)
	{
		for (auto observer : observers)
		{
			observer->field_changed(source, field_name);
		}
	}

	void subscribe(Observer<T>& observer)
	{
		observers.push_back(&observer);
	}

	void unsubscribe(Observer<T>& observer)
	{
		observers.erase(
			// remove removes the observer from the vector and returns the new end iterator.
			// So we are giving erase new end after removing the element and old end before removing
			// Therefore it removes the remaining elements.
			remove(observers.begin(), observers.end(), &observer),
			observers.end()
		);
	}
};