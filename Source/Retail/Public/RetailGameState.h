#pragma once

#include <Runtime/Engine/Classes/GameFramework/ManagerFramework/ManagedGameState.h>

#include <ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h>

class UGridRenderManager;

#include "RetailGameState.generated.h"

UCLASS()
class ARetailGameState : public AManagedGameState
	, public IObjectMessagingListenerInterface
{
	GENERATED_BODY()

public:

	ARetailGameState(const FObjectInitializer& ObjectInitialiser);

	//AManagedGameState
	virtual void BuildManagerList() override;
	//~AManagedGameState

	//IObjectMessagingListenerInterface
	FObjectMessagingListener& GetListener() override { return Listener; }
	//~IObjectMessagingListenerInterface

private:

	FObjectMessagingListener Listener;
};