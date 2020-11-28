#include "Runtime/BuildFramework/Public/Footprint/BuildFootprint.h"

#include "Runtime/BuildFramework/Public/BuildInfo/BuildInfo.h"

#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#endif //!UE_BUILD_SHIPPING

FBuildFootprint::FBuildFootprint(const UBuildInfo& InSourceBuildInfo)
	: Extent()
	, PointBuckets()
	, SourceBuildInfo(&InSourceBuildInfo)
{
	Reset(&InSourceBuildInfo);
}

FBuildFootprint::FBuildFootprint()
	: Extent()
	, PointBuckets()
	, SourceBuildInfo(nullptr)
{
	Reset(nullptr);
}

void FBuildFootprint::Reset(const UBuildInfo* InBuildInfo)
{
	PointBuckets.Empty();
	Extent = FIntVector::ZeroValue;
	SourceBuildInfo = InBuildInfo;
}

void FBuildFootprint::AddPoint(const FVector& InLocation, const FIntVector& InPointIndex)
{
	AddPoint(InLocation, 0.f, InPointIndex);
}

void FBuildFootprint::AddPoint(const FVector& InLocation, const float InYaw, const FIntVector& InPointIndex)
{
	const EBuildPointType CurrPointType = GetPointTypeForIndex(InPointIndex);
	const FBuildPoint NewPoint(InLocation, FRotator(0.f, InYaw, 0.f), InPointIndex, CurrPointType);

	if (FBuildPointBucket* ExistingBucket = PointBuckets.Find(CurrPointType))
	{
		ExistingBucket->Add(NewPoint);
	}
	else
	{
		PointBuckets.Add(CurrPointType, NewPoint);
	}

	LastBuildPoint = NewPoint;
}

FVector FBuildFootprint::Last() const
{
	return LastBuildPoint.GetLocation();
}

EBuildPointType FBuildFootprint::GetPointTypeForIndex(const FIntVector& InPointIndex) const
{
	if (
		( InPointIndex == FIntVector(0, 0, 0)) ||
		( InPointIndex == FIntVector(0, Extent.Y, 0)) ||
		( InPointIndex == FIntVector(Extent.X, 0, 0)) ||
		( InPointIndex == Extent))
	{
		return EBuildPointType::Corner;
	}
	else if (
		( Extent.X == 2 && InPointIndex == FIntVector(1, 0, 0)) ||
		( Extent.Y == 2 && InPointIndex == FIntVector(0, 1, 0)) ||
		(Extent.Y == 2 && InPointIndex == FIntVector(Extent.X, 1, 0)) ||
		(Extent.X == 2 && InPointIndex == FIntVector(1, Extent.Y, 0)))
	{
		return EBuildPointType::CornerToCornerBridge;
	}
	else if (
		(InPointIndex == FIntVector(0, 1, 0)) ||
		(InPointIndex == FIntVector(1, 0, 0)) ||
		(InPointIndex == FIntVector(Extent.X - 1, 0, 0)) ||
		(InPointIndex == FIntVector(Extent.X, 1, 0)) ||
		(InPointIndex == FIntVector(Extent.X, Extent.Y - 1, 0)) ||
		(InPointIndex == FIntVector(Extent.X - 1, Extent.Y, 0)) ||
		(InPointIndex == FIntVector(0, Extent.Y - 1, 0)) ||
		(InPointIndex == FIntVector(1, Extent.Y, 0)))
	{
		return EBuildPointType::CornerBridge;
	}
	else if (InPointIndex.X == 0 
		|| InPointIndex.X == Extent.X 
		|| InPointIndex.Y == 0 
		|| InPointIndex.Y == Extent.Y)
	{
		return EBuildPointType::Straight;
	}

	return EBuildPointType::INVALID;
}

void FBuildFootprint::TryAlignCornerBridges()
{
	if (FBuildPointBucket* CornerBridgeBucket = PointBuckets.Find(EBuildPointType::CornerBridge))
	{
		for (FBuildPoint& BridgePoint : CornerBridgeBucket->Points)
		{
			const FVector BridgePointLoc = BridgePoint.GetLocation();

			if (const FBuildPointBucket* CornerBucket = PointBuckets.Find(EBuildPointType::Corner))
			{
				const FBuildPoint* CurrentClosestPoint = nullptr;
				int32 DistToNearestCorner = 10000000;

				for (const FBuildPoint& CornerPoint : CornerBucket->Points)
				{
					const FIntVector DistanceToPoint = CornerPoint.GetIndex() - BridgePoint.GetIndex();
					const int32 DistanceFromSize = FMath::Abs(DistanceToPoint.Size());

					if (DistanceFromSize == DistToNearestCorner)
					{
						const float DistRawToExistingClosest = FVector::DistSquared(CurrentClosestPoint->GetLocation(), BridgePointLoc);
						const float DistRawToPotentialClosest = FVector::DistSquared(CornerPoint.GetLocation(), BridgePointLoc);

						CurrentClosestPoint = DistRawToPotentialClosest < DistRawToExistingClosest ? &CornerPoint : CurrentClosestPoint;
						DistToNearestCorner = DistanceFromSize;
					}
					else if (CurrentClosestPoint == nullptr || DistanceFromSize < DistToNearestCorner)
					{
						CurrentClosestPoint = &CornerPoint;
						DistToNearestCorner = DistanceFromSize;
					}
				}

				BridgePoint.SetRotation(UKismetMathLibrary::FindLookAtRotation(CurrentClosestPoint->GetLocation(), BridgePointLoc));
			}
		}
	}
}

#if !UE_BUILD_SHIPPING
void FBuildFootprint::Visualise(const UWorld& InWorld, const float InGridSize)
{
	FlushPersistentDebugLines(&InWorld);
	FlushDebugStrings(&InWorld);

	for (const TPair<EBuildPointType, FBuildPointBucket>& Bucket : PointBuckets)
	{
		for (const FBuildPoint& Point : Bucket.Value.Points)
		{
			const FVector PointLoc = Point.GetLocation();

			DrawDebugSphere(&InWorld, PointLoc, InGridSize * 0.5f, 12, FColor::White, true);
			const FString PointText = FString::Printf(TEXT("[%i, %i] - %s"), Point.GetIndex().X, Point.GetIndex().Y, *UEnum::GetValueAsString(Point.GetType()));

			DrawDebugString(&InWorld, PointLoc + FVector(0.f, 0.f, 100.f), PointText, nullptr, FColor::White, 60.f, true);

			switch (Point.GetType())
			{
			case EBuildPointType::Corner:
				DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 50.f), FQuat::Identity, FColor::White, true);
				break;
			case EBuildPointType::CornerBridge:
				DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 50.f), FQuat::Identity, FColorList::Red, true);
				break;
			case EBuildPointType::CornerToCornerBridge:
				DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 50.f), FQuat::Identity, FColorList::Green, true);
				break;
			case EBuildPointType::Straight:
				DrawDebugSolidBox(&InWorld, PointLoc, FVector(InGridSize * 0.5f, InGridSize * 0.5f, 50.f), FQuat::Identity, FColorList::Blue, true);
			default:
				break;
			}
		}
	}
}
#endif //!UE_BUILD_SHIPPING