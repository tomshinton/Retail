#pragma once

#include <Runtime/Engine/Classes/GameFramework/Actor.h>
#include "Runtime/BuildFramework/Public/Footprint/BuildPointType.h"

#include "Ghost.generated.h"

class FBuildFootprint;
class UHierarchicalInstancedStaticMeshComponent;
class USceneComponent;
class UStaticMesh;

UCLASS()
class AGhost : public AActor
{
	GENERATED_BODY()

public:
	
	AGhost(const FObjectInitializer& ObjectInitializer);

	void UpdateFootprint(const FBuildFootprint& InFootprint);
	void Reset();

private:

	void Rebuild(const FBuildFootprint& InFootprint);

	UHierarchicalInstancedStaticMeshComponent& GetComponentForMesh(UStaticMesh& InMesh);
	UHierarchicalInstancedStaticMeshComponent& CreateInstanceForMesh(UStaticMesh& InMesh);

	UPROPERTY()
	USceneComponent* GhostRoot;

	UPROPERTY()
	TArray<UHierarchicalInstancedStaticMeshComponent*> PreviewMeshes;
};