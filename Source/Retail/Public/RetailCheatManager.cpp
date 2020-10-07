#include "Retail/Public/RetailCheatManager.h"

#include <Runtime/BuildFramework/Public/BuildInterface.h>

URetailCheatManager::URetailCheatManager()
{

}

void URetailCheatManager::StartBuildingFromClass(const FSoftObjectPath& InClassPath)
{
	if (IBuildInterface* BuildInterface = GetLocalPawn()->GetInterface<IBuildInterface>())
	{
		BuildInterface->StartBuildFromClass(InClassPath);
	}
}
