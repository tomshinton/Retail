#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

class FBuildPoint
{

public:

	FBuildPoint(const FVector& InLocation, const FIntVector& InPointIndex, const EBuildPointType InType);

	FVector GetLocation() const { return Location; }
	FTransform GetTransform() const 
	{
		return FTransform(FRotator::ZeroRotator, GetLocation(), FVector(1.f, 1.f, 1.f));
	};

	FIntVector GetIndex() const { return PointIndex; }
	EBuildPointType GetType() const { return Type; }

	bool operator==(const FVector& InLocation) const
	{
		return Location == InLocation;
	}

	bool operator==(const FBuildPoint& InBuildPoint) const
	{
		return InBuildPoint.Location == Location;
	}

private:

	FVector Location;

	//How does this point compare to it's parent extent?
	FIntVector PointIndex;
	EBuildPointType Type;
};