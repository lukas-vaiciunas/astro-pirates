#include "Objective.h"

Objective::Objective(const std::unordered_map<uint16_t, uint16_t> &requirements) :
	requirements_(requirements)
{}

void Objective::update(uint16_t id)
{
	for (auto it = requirements_.begin(); it != requirements_.end(); ++it)
	{
		if (it->first == id)
		{
			if (it->second > 0)
				--it->second;

			break;
		}
	}
}

bool Objective::isDone() const
{
	for (auto it = requirements_.cbegin(); it != requirements_.cend(); ++it)
	{
		if (it->second > 0)
			return false;
	}

	return true;
}