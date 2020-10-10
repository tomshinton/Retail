#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

FBuildPoint::FBuildPoint(const FVector& InLocation,const FIntVector& InPointIndex, const EBuildPointType InType)
	: Location(InLocation)
	, PointIndex(InPointIndex)
	, Type(InType)
{

}
