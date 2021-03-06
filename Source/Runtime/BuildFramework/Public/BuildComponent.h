#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "Runtime/BuildFramework/Public/BuildInterface.h"

#include <Runtime/CoreUObject/Public/Serialization/AsyncLoader.h>
#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>

#include "BuildComponent.generated.h"

class AGhost;
class APlayerController;
class IObjectMessagingListenerInterface;
class UBuildInfo;
class UBuildPolicyBase;

struct FBuildPointBucket;

UCLASS(MinimalAPI)
class UBuildComponent : public UActorComponent
	, public IBuildInterface
{
	GENERATED_BODY()

public:

	UBuildComponent(const FObjectInitializer& ObjectInitialiser);

	//~UActorComponent
	void BeginPlay() override;
	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
	//UActorComponent

	//IBuildInterface
	void StartBuildFromClass(const FSoftObjectPath& InClass) override;
	//~IBuildInterface

private:

	void StartBuild();
	void EndBuild();
	void CancelBuild();

	UBuildPolicyBase* GetPolicy();

	UPROPERTY(Transient)
	UBuildInfo* CurrentBuildInfo;

	UPROPERTY(Transient)
	UBuildPolicyBase* CurrentBuildPolicy;

	TUniquePtr<FAsyncLoader> AsyncLoader;

	TWeakObjectPtr<APlayerController> WeakController;

	UPROPERTY()
	AGhost* Ghost;
};