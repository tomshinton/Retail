#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

class FBuildPoint
{

public:

	FBuildPoint(const FVector& InLocation, const FIntVector& InPointIndex, const EBuildPointType InType);

	FVector GetLocation() const { return Location; }
	FIntVector GetIndex() const { return PointIndex; }
	EBuildPointType GetType() const { return Type; }

private:

	FVector Location;

	//How does this point compare to it's parent extent?
	FIntVector PointIndex;
	EBuildPointType Type;
};