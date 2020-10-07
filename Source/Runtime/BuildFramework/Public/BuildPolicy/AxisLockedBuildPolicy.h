#pragma once

#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"

#include "AxisLockedBuildPolicy.generated.h"

UCLASS()
class UAxisLockedBuildPolicy : public UBuildPolicyBase
{
	GENERATED_BODY()

public:

	UAxisLockedBuildPolicy()
	{};

	virtual void GeneratePoints(TArray<FVector>& OutGeneratedPoints) const override
	{
		if (DiffUnit.X > DiffUnit.Y)
		{
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
				OutGeneratedPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
			}
		}
		else
		{
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutGeneratedPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
			}
		}
	}
};