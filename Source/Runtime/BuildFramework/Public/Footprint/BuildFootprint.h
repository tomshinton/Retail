#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

class UBuildInfo;

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

class FBuildFootprint
{
public:

	FBuildFootprint();
	BUILDFRAMEWORK_API FBuildFootprint(const UBuildInfo& InSourceBuildInfo);

	void Reset(const UBuildInfo* InBuildInfo);

	void AddPoint(const FVector& InLocation, const FIntVector& InPointIndex);
	void AddPoint(const FVector& InLocation, const float InYaw, const FIntVector& InPointIndex);

	FVector Last() const;

	FIntVector Extent;
	TMap<EBuildPointType, FBuildPointBucket> PointBuckets;
	FBuildPoint LastBuildPoint;

	int8 XDir;
	int8 YDir;

#if !UE_BUILD_SHIPPING
	void Visualise(const UWorld& InWorld, const float InGridSize);
#endif //!UE_BUILD_SHIPPING

	BUILDFRAMEWORK_API EBuildPointType GetPointTypeForIndex(const FIntVector& InLocation) const;
	void TryAlignCornerBridges();

	UPROPERTY(Transient)
	const UBuildInfo* SourceBuildInfo;
};
