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

	virtual void GeneratePoints(FBuildFootprint& OutBuildingFootprint) const override
	{
		if (DiffUnit.X > DiffUnit.Y)
		{
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
				OutBuildingFootprint.AddPoint(FVector(NewX, StartLoc.Y, StartLoc.Z), FIntVector(x, 0, 0));
			}
		}
		else
		{
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutBuildingFootprint.AddPoint(FVector(StartLoc.X, NewY, StartLoc.Z), -90.f, FIntVector(0, y, 0));
			}
		}
	}
};