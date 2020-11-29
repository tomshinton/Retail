#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "StructureInterface.generated.h"

class FBuildFootprint;

UINTERFACE(MinimalAPI)
class UStructureInterface : public UInterface
{
	GENERATED_BODY()
};

class IStructureInterface
{
	GENERATED_BODY()

public:

	virtual void SpawnBuildingFromFootprint(const FBuildFootprint& InFootprint) = 0;
};
