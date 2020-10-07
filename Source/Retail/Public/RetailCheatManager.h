#pragma once

#include <Runtime/Engine/Classes/GameFramework/CheatManager.h>

#include "RetailCheatManager.generated.h"

UCLASS()
class URetailCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	URetailCheatManager();

	UFUNCTION(Exec)
	void StartBuildingFromClass(const FSoftObjectPath& InClassPath);
};