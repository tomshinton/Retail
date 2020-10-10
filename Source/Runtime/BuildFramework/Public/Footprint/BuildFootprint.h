#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

class FBuildFootprint
{
public:

	FBuildFootprint();

	void Reset();

	void AddPoint(const FVector& InLocation, const FIntVector& InPointIndex);
	FVector Last() const;

	FIntVector Extent;
	TArray<FBuildPoint> Points;

#if !UE_BUILD_SHIPPING
	void Visualise(const UWorld& InWorld, const float InGridSize);
#endif //!UE_BUILD_SHIPPING

private:

	EBuildPointType GetPointTypeForLocation(const FVector& InLocation) const;
};
