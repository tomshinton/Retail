#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "RenderSetRecieverInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class URenderSetRecieverInterface : public UInterface
{
	GENERATED_BODY()
};

class IRenderSetRecieverInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void SetMesh(const UStaticMesh* Mesh);
};
