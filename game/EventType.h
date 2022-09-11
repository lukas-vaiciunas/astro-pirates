#pragma once

#include <cinttypes>

enum class EventType : uint8_t
{
	ChangeDriverState,
	Exit,
	TargetDestroyed,
	UpdateObjectiveUi,
	PlayerHurt,
	PlayerDeath
};