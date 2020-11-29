#pragma once

#include "Runtime/BuildFramework/Public/Footprint/BuildFootprint.h"

#include "BuildComponentEvents.generated.h"

USTRUCT()
struct FOnBuildEnded
{
	GENERATED_BODY()

public:

	FOnBuildEnded()
	{};

	explicit FOnBuildEnded(const FBuildFootprint& InFootprint)
		: Footprint(InFootprint)
	{}

	FBuildFootprint Footprint;
};