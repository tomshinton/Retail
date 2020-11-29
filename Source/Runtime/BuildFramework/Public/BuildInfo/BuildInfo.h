#pragma once

#include <Runtime/Engine/Classes/Engine/DataAsset.h>
#include <Runtime/InputCore/Classes/InputCoreTypes.h>
#include "Runtime/BuildFramework/Public/BuildInfo/BuildingRenderSet.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

#include "BuildInfo.generated.h"

class UBuildingRenderSet;
class UBuildPolicyBase;
class UStaticMesh;

UCLASS(MinimalAPI)
class UBuildInfo : public UDataAsset 
{
	GENERATED_BODY()

public:

	UBuildInfo()
		: PrimaryBuildPolicy(nullptr)
		, AlternativePolicies()
		, ClearBuildActionOnceComplete(true)
		, RenderSet(nullptr)
		, BuildingActorClass(nullptr)
#if WITH_EDITORONLY_DATA
		, FolderPath("Buildings")
#endif //WITH_EDITORONLY_DATA
	{
	};

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Construction")
	UBuildPolicyBase* PrimaryBuildPolicy;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Construction")
	TMap<FKey, UBuildPolicyBase*> AlternativePolicies;

	UPROPERTY(EditDefaultsOnly, Category = "Construction")
	bool ClearBuildActionOnceComplete;

	UPROPERTY(EditDefaultsOnly, Category = "Rendering")
	UBuildingRenderSet* RenderSet;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> BuildingActorClass;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "Editor | Organisation")
	FString FolderPath;
#endif //WITH_EDITORONLY_DATA

	const UStaticMesh* GetMeshForPoint(const EBuildPointType InBuildPoint) const
	{
		if (RenderSet != nullptr)
		{
			return RenderSet->Meshes[static_cast<int32>(InBuildPoint)];
		}

		return nullptr;
	}
};