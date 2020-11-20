#pragma once

#include "Runtime/Engine/Classes/Engine/DataAsset.h"

#include <Runtime/BuildFramework/Public/Footprint/BuildPointType.h>

class UStaticMesh;

#include "BuildingRenderSet.generated.h"

UCLASS()
class UBuildingRenderSet : public UDataAsset 
{
	GENERATED_BODY()

public:

	UBuildingRenderSet()
	{};

	UPROPERTY(EditDefaultsOnly)
	const UStaticMesh* Meshes[EBuildPointType::INVALID];
};