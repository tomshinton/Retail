#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"


FBuildPoint::FBuildPoint()
	: Location(FVector::ZeroVector)
	, Rotation(FRotator::ZeroRotator)
	, PointIndex()
	, Type(EBuildPointType::INVALID)
{

}

FBuildPoint::FBuildPoint(const FVector& InLocation, const FRotator& InRotation, const FIntVector& InPointIndex, const EBuildPointType InType)
	: Location(InLocation)
	, Rotation(InRotation)
	, PointIndex(InPointIndex)
	, Type(InType)
{

}
