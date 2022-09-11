#pragma once

#include <random>

class Rng
{
public:
	Rng(const Rng &) = delete;
	Rng &operator=(const Rng &) = delete;

	static Rng &getInstance();

	std::mt19937 &getEng();
private:
	Rng();
	~Rng() {}

	std::mt19937 eng_;
};