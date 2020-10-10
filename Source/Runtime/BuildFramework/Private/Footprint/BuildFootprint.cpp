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
	Points.Emplace(InLocation, InPointIndex, GetPointTypeForIndex(InPointIndex));
}

FVector FBuildFootprint::Last() const
{
	return Points.Last().GetLocation();
}

EBuildPointType FBuildFootprint::GetPointTypeForIndex(const FIntVector& InPointIndex) const
{
	if (InPointIndex == FIntVector(0, 0, 0) || InPointIndex == FIntVector(0, Extent.Y, 0) || InPointIndex == FIntVector(Extent.X, 0, 0) || InPointIndex == Extent)
	{
		return EBuildPointType::Corner;
	}
	else if ((InPointIndex.X == 0 || InPointIndex.X == Extent.X) ||	(InPointIndex.Y == 0 || InPointIndex.Y == Extent.Y))
	{
		return EBuildPointType::Straight;
	}

	return EBuildPointType::INVALID;
}

#if !UE_BUILD_SHIPPING
void FBuildFootprint::Visualise(const UWorld& InWorld, const float InGridSize)
{
	FlushPersistentDebugLines(&InWorld);

	for (const FBuildPoint& Point : Points)
	{
		const FVector PointLoc = Point.GetLocation();

		DrawDebugSphere(&InWorld, PointLoc, InGridSize * 0.5f, 12, FColor::White, true);
		const FString PointText = FString::Printf(TEXT("[%i, %i]"), Point.GetIndex().X, Point.GetIndex().Y);

		DrawDebugString(&InWorld, PointLoc + FVector(0.f, 0.f, 100.f), PointText, nullptr, FColor::White, true, 20.f);
	
		switch (Point.GetType())
		{
		case EBuildPointType::Corner:
			DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 100.f), FQuat::Identity, FColor::Green, true);
			break;
		case EBuildPointType::Straight:
			DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 100.f), FQuat::Identity, FColor::White, true);
			break;
		case EBuildPointType::INVALID:
		default:
			DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 100.f), FQuat::Identity, FColor::Red, true);
			break;
		}
	}
}
#endif //!UE_BUILD_SHIPPING