#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

FBuildPoint::FBuildPoint(const FVector& InLocation, const FRotator& InRotation, const FIntVector& InPointIndex, const EBuildPointType InType)
	: Location(InLocation)
	, Rotation(InRotation)
	, PointIndex(InPointIndex)
	, Type(InType)
{

}
