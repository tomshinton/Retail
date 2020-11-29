#include "Retail/Public/RetailGameState.h"

#include <Runtime/Structure/Public/StructureManager/StructureManager.h>

ARetailGameState::ARetailGameState(const FObjectInitializer& ObjectInitialiser)
{

}

void ARetailGameState::BuildManagerList()
{
	ManagerList.Emplace(UStructureManager::StaticClass(), [this](UObject& SpawnedManager) { InitialiseStructureManager(SpawnedManager); });
}

void ARetailGameState::InitialiseStructureManager(UObject& InManager)
{
	UStructureManager* Manager = CastChecked<UStructureManager>(&InManager);
	Manager->Init(*GetWorld());
}
