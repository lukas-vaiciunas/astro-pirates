#pragma once

#include <vector>

template<typename T>
class Pool
{
public:
	Pool(uint16_t capacity);
	virtual ~Pool();

	typename std::vector<T *>::iterator begin();
	typename std::vector<T *>::iterator end();

	typename std::vector<T *>::const_iterator begin() const;
	typename std::vector<T *>::const_iterator end() const;

	void add(T *object);

	bool isFull() const;
protected:
	std::vector<T *> objects_;
	uint16_t capacity_;
	uint16_t numLive_;

	void removeAtIndex_(uint16_t index);
};

template<typename T>
Pool<T>::Pool(uint16_t capacity) :
	objects_(capacity, nullptr),
	capacity_(capacity),
	numLive_(0)
{}

template<typename T>
Pool<T>::~Pool()
{
	for (uint16_t i = 0; i < numLive_; ++i)
	{
		delete objects_[i];
	}
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::begin()
{
	return objects_.begin();
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::end()
{
	return objects_.begin() + numLive_;
}

template<typename T>
typename std::vector<T *>::const_iterator Pool<T>::begin() const
{
	return objects_.begin();
}

template<typename T>
typename std::vector<T *>::const_iterator Pool<T>::end() const
{
	return objects_.begin() + numLive_;
}

template<typename T>
void Pool<T>::add(T *object)
{
	objects_[numLive_++] = object;
}

template<typename T>
bool Pool<T>::isFull() const
{
	return numLive_ >= capacity_;
}

template<typename T>
void Pool<T>::removeAtIndex_(uint16_t index)
{
	delete objects_[index];
	--numLive_;
	objects_[index] = objects_[numLive_];
	objects_[numLive_] = nullptr;
}