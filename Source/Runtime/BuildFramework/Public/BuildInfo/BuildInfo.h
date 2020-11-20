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
	{
	};

	UPROPERTY(Instanced, EditDefaultsOnly)
	UBuildPolicyBase* PrimaryBuildPolicy;

	UPROPERTY(Instanced, EditDefaultsOnly)
	TMap<FKey, UBuildPolicyBase*> AlternativePolicies;

	UPROPERTY(EditDefaultsOnly, Category = "Rendering")
	UBuildingRenderSet* RenderSet;

	const UStaticMesh* GetMeshForPoint(const EBuildPointType InBuildPoint) const
	{
		if (RenderSet != nullptr)
		{
			return RenderSet->Meshes[static_cast<int32>(InBuildPoint)];
		}

		return nullptr;
	}
};