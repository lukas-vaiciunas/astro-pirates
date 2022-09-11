#include "Rng.h"

Rng::Rng() :
	eng_(std::random_device()())
{}

Rng &Rng::getInstance()
{
	static Rng instance;
	return instance;
}

std::mt19937 &Rng::getEng()
{
	return eng_;
}