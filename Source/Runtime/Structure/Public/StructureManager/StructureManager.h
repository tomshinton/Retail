#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include <Runtime/Structure/Public/StructureManager/StructureInterface.h>

#include "StructureManager.generated.h"

UCLASS(MinimalAPI)
class UStructureManager : public UObject
	, public IStructureInterface
{
	GENERATED_BODY()

public:

	UStructureManager();
	STRUCTURE_API void Init(UWorld& InWorld);

private:

	//IStructureInterface
	void SpawnBuildingFromFootprint(const FBuildFootprint& InFootprint) override;
	//~IStructureInterface

	void RegisterEvents();

	UPROPERTY()
	UWorld* World;
};
