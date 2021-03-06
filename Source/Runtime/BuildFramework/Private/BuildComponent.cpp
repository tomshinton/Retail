#include "Runtime/BuildFramework/Public/BuildComponent.h"
#include "Runtime/BuildFramework/Public/BuildInfo/BuildInfo.h"
#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"
#include "Runtime/BuildFramework/Public/Events/BuildComponentEvents.h"
#include "Runtime/BuildFramework/Public/Ghost/Ghost.h"

#include <ObjectMessaging/Public/Sender/ObjectMessagingFunctions.h>
#include <Runtime/Engine/Classes/GameFramework/GameStateBase.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>

DEFINE_LOG_CATEGORY_STATIC(BuildComponentLog, Log, All);

namespace BuildComponentBindings
{
	const FName Build = TEXT("Build");
	const FName CancelBuild = TEXT("CancelBuild");
}

UBuildComponent::UBuildComponent(const FObjectInitializer& ObjectInitialiser)
	: CurrentBuildInfo(nullptr)
	, CurrentBuildPolicy(nullptr)
	, AsyncLoader(MakeUnique<FAsyncLoader>())
	, WeakController()
{

}

void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		WeakController = World->GetFirstPlayerController();

		if (!WeakController.IsValid())
		{
			UE_LOG(BuildComponentLog, Error, TEXT("Could not source local player controller"));
		}

		if (AGhost* SpawnedGhost = World->SpawnActor<AGhost>(AGhost::StaticClass(), FTransform::Identity))
		{
			Ghost = SpawnedGhost;
		}
	}
}

void UBuildComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	PlayerInputComponent.BindAction(BuildComponentBindings::Build, IE_Pressed, this, &UBuildComponent::StartBuild);
	PlayerInputComponent.BindAction(BuildComponentBindings::Build, IE_Released, this, &UBuildComponent::EndBuild);

	PlayerInputComponent.BindAction(BuildComponentBindings::CancelBuild, IE_Pressed, this, &UBuildComponent::CancelBuild);
}

void UBuildComponent::StartBuildFromClass(const FSoftObjectPath& InClass)
{
	AsyncLoader->RequestLoad<UBuildInfo>(InClass, [WeakThis = TWeakObjectPtr<UBuildComponent>(this), this](UBuildInfo& LoadedClass)
	{
		if (WeakThis.IsValid())
		{
			if (CurrentBuildInfo != nullptr)
			{
				CancelBuild();
			}

			CurrentBuildInfo = &LoadedClass;
			UE_LOG(BuildComponentLog, Log, TEXT("Initiating build from %s"), *LoadedClass.GetName());
		}
	}); 
}

void UBuildComponent::StartBuild()
{
	if (CurrentBuildInfo != nullptr)
	{
		if (UBuildPolicyBase* IdealPolicy = GetPolicy())
		{
			UE_LOG(BuildComponentLog, Log, TEXT("Starting build using policy %s"), *IdealPolicy->GetName());
			CurrentBuildPolicy = IdealPolicy;
			IdealPolicy->Start(*Ghost, *CurrentBuildInfo);
		}
		else
		{
			UE_LOG(BuildComponentLog, Error, TEXT("% returned no valid policy"), *CurrentBuildInfo->GetName());
		}
	}
}

void UBuildComponent::EndBuild()
{
	if (CurrentBuildInfo != nullptr && CurrentBuildPolicy != nullptr)
	{
		UE_LOG(BuildComponentLog, Log, TEXT("Ending %s's using policy %s"), *CurrentBuildInfo->GetName(), *CurrentBuildPolicy->GetName());

		if (UWorld* World = GetWorld())
		{
			ObjectMessagingFunctions::SendMessage<FOnBuildEnded>(*World->GetGameState(), FOnBuildEnded(*CurrentBuildPolicy->GetFootprint()));
		}

		CurrentBuildPolicy->End();

		if (CurrentBuildInfo->ClearBuildActionOnceComplete)
		{
			CurrentBuildPolicy = nullptr;
			CurrentBuildInfo = nullptr;
		}
	}
}

void UBuildComponent::CancelBuild()
{
	if (CurrentBuildPolicy == nullptr && CurrentBuildInfo != nullptr)
	{
		UE_LOG(BuildComponentLog, Log, TEXT("Ending %s's build - build not currently active so no ghost to cleanup"), *CurrentBuildInfo->GetName());

		//we're not actively building
		CurrentBuildInfo = nullptr;
	}
	else if (CurrentBuildPolicy != nullptr)
	{
		UE_LOG(BuildComponentLog, Log, TEXT("Cancelling %s's using policy %s"), *CurrentBuildInfo->GetName(), *CurrentBuildPolicy->GetName());

		CurrentBuildPolicy->Cancel();
		CurrentBuildPolicy = nullptr;
	}
}

UBuildPolicyBase* UBuildComponent::GetPolicy()
{
	if (CurrentBuildInfo != nullptr)
	{
		UBuildPolicyBase* NewPolicy = CurrentBuildInfo->PrimaryBuildPolicy;

		if (APlayerController* StrongController = WeakController.Get())
		{
			const TMap<FKey, UBuildPolicyBase*> Policies = CurrentBuildInfo->AlternativePolicies;
			for (const TPair<FKey, UBuildPolicyBase*>& AlternativePolicy : Policies)
			{
				if (StrongController->IsInputKeyDown(AlternativePolicy.Key))
				{
					NewPolicy = AlternativePolicy.Value;
					break;
				}
			}
		}

		//As policies are instanced, duplicate them here so they can operate autonomously
		return DuplicateObject<UBuildPolicyBase>(NewPolicy, this);
	}
	
	return nullptr;
}
