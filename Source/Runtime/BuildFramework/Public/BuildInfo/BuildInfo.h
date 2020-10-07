#pragma once

#include <Runtime/Engine/Classes/Engine/DataAsset.h>
#include <Runtime/InputCore/Classes/InputCoreTypes.h>

#include "BuildInfo.generated.h"

class UBuildPolicyBase;

UCLASS()
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
};