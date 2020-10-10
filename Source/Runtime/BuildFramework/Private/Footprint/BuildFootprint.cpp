#include "Runtime/BuildFramework/Public/Footprint/BuildFootprint.h"

#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#endif //!UE_BUILD_SHIPPING

FBuildFootprint::FBuildFootprint()
{
	Reset();
}

void FBuildFootprint::Reset()
{
	Points.Empty();
	Extent = FIntVector::ZeroValue;
}

void FBuildFootprint::AddPoint(const FVector& InLocation, const FIntVector& InPointIndex)
{
	Points.Emplace(InLocation, InPointIndex, GetPointTypeForLocation(InLocation));
}

FVector FBuildFootprint::Last() const
{
	return Points.Last().GetLocation();
}

EBuildPointType FBuildFootprint::GetPointTypeForLocation(const FVector& InLocation) const
{
	return EBuildPointType::INVALID;
}

#if !UE_BUILD_SHIPPING
void FBuildFootprint::Visualise(const UWorld& InWorld, const float InGridSize)
{
	FlushPersistentDebugLines(&InWorld);

	for (const FBuildPoint& Point : Points)
	{
		DrawDebugSphere(&InWorld, Point.GetLocation(), InGridSize * 0.5f, 12, FColor::White, true);
		const FString PointText = FString::Printf(TEXT("[%i, %i]"), Point.GetIndex().X, Point.GetIndex().Y);

		DrawDebugString(&InWorld, Point.GetLocation() + FVector(0.f, 0.f, 100.f), PointText, nullptr, FColor::White, true);
	}
}
#endif //!UE_BUILD_SHIPPING