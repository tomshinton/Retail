#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

class UBuildInfo;

class FBuildFootprint
{
public:

	FBuildFootprint();
	BUILDFRAMEWORK_API FBuildFootprint(const UBuildInfo& InSourceBuildInfo);

	void Reset(const UBuildInfo* InBuildInfo);

	void AddPoint(const FVector& InLocation, const FIntVector& InPointIndex);
	FVector Last() const;

	FIntVector Extent;
	TArray<FBuildPoint> Points;

#if !UE_BUILD_SHIPPING
	void Visualise(const UWorld& InWorld, const float InGridSize);
#endif //!UE_BUILD_SHIPPING

	BUILDFRAMEWORK_API EBuildPointType GetPointTypeForIndex(const FIntVector& InLocation) const;

	UPROPERTY(Transient)
	const UBuildInfo* SourceBuildInfo;
};
