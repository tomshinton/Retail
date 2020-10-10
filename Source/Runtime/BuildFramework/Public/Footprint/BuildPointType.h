#pragma once

#include "BuildPointType.generated.h"

UENUM()
enum class EBuildPointType : uint8 
{
	Corner,
	Straight,
	INVALID
};