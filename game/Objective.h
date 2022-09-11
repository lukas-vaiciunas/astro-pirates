#pragma once

#include <unordered_map>

class Objective
{
public:
	Objective(const std::unordered_map<uint16_t, uint16_t> &requirements);

	void update(uint16_t id);

	bool isDone() const;
private:
	std::unordered_map<uint16_t, uint16_t> requirements_;
};