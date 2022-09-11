#pragma once

#include <cinttypes>

class Identifiable
{
public:
	Identifiable(uint16_t id);
	virtual ~Identifiable() {}

	uint16_t getId() const;
protected:
	uint16_t id_;
};