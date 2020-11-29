#include "Runtime/Structure/Public/StructureManager/StructureManager.h"
#include "Runtime/Structure/Public/Rendering/RenderSetRecieverInterface.h"

#include <Runtime/BuildFramework/Public/BuildInfo/BuildInfo.h>
#include <Runtime/BuildFramework/Public/Footprint/BuildFootprint.h>
#include <Runtime/BuildFramework/Public/Footprint/BuildPointBucket.h>
#include <Runtime/BuildFramework/Public/Footprint/BuildPointType.h>
#include <Runtime/BuildFramework/Public/Events/BuildComponentEvents.h>

#include <Runtime/Engine/Classes/GameFramework/GameStateBase.h>
#include <ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#endif //!UE_BUILD_SHIPPING

DEFINE_LOG_CATEGORY_STATIC(StructureManagerLog, Log, Log)

UStructureManager::UStructureManager()
	: World(nullptr)
{

}

void UStructureManager::Init(UWorld& InWorld)
{
	World = &InWorld;

	RegisterEvents();
}

void UStructureManager::SpawnBuildingFromFootprint(const FBuildFootprint& InFootprint)
{
	for (const TPair<EBuildPointType, FBuildPointBucket>& Bucket : InFootprint.PointBuckets)
	{
		for (const FBuildPoint& Point : Bucket.Value.Points)
		{
			const UBuildInfo& SourceBuildInfo = *InFootprint.SourceBuildInfo;
			if (AActor* SpawnedActor = World->SpawnActor<AActor>(SourceBuildInfo.BuildingActorClass, Point.GetTransform()))
			{
#if WITH_EDITORONLY_DATA
				const FString NewPath = FString::Printf(TEXT("Structures/%s"), *SourceBuildInfo.FolderPath);
				SpawnedActor->SetFolderPath(FName(*NewPath));
#endif //WITH_EDITORONLY_DATA

				if (SpawnedActor->Implements<URenderSetRecieverInterface>())
				{
					IRenderSetRecieverInterface::Execute_SetMesh(SpawnedActor, SourceBuildInfo.GetMeshForPoint(Point.GetType()));
				}
			}
		}
	}
}

void UStructureManager::RegisterEvents()
{
	if (AGameStateBase* GameState = World->GetGameState<AGameStateBase>())
	{
		if (IObjectMessagingListenerInterface* ObjectMessagingInterface = GameState->GetInterface<IObjectMessagingListenerInterface>())
		{
			TWeakObjectPtr<UStructureManager> WeakThis = TWeakObjectPtr<UStructureManager>(this);
			ObjectMessagingInterface->GetListener().Bind<FOnBuildEnded>([WeakThis](const FOnBuildEnded& InEv)
			{
				if (UStructureManager* StrongThis = WeakThis.Get())
				{
					StrongThis->SpawnBuildingFromFootprint(InEv.Footprint);
				}
			});
		}
	}
}

