#pragma once

#include "BuildPointType.generated.h"

UENUM()
enum class EBuildPointType : uint8
{
	Corner,
	CornerBridge,
	CornerToCornerBridge,
	Straight,
	INVALID UMETA(Hidden)
};