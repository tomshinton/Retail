#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

struct FBuildPointBucket
{
	FBuildPointBucket()
		: Points()
	{};

	FBuildPointBucket(const FBuildPoint& InSeedPoint)
		: Points()
	{
		Points.Add(InSeedPoint);
	};

	void Add(const FBuildPoint& InPoint)
	{
		Points.AddUnique(InPoint);
	}

	TArray<FBuildPoint> Points;
};
