#include "Identifiable.h"

Identifiable::Identifiable(uint16_t id) :
	id_(id)
{}

uint16_t Identifiable::getId() const
{
	return id_;
}