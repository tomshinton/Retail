#pragma once

#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"

#include "LinearBuildPolicy.generated.h"

UCLASS()
class ULinearBuildPolicy : public UBuildPolicyBase
{
	GENERATED_BODY()

public:

	ULinearBuildPolicy()
	{};

	virtual void GeneratePoints(FBuildFootprint& OutBuildingFootprint) const override
	{
		if (DiffUnit.X > DiffUnit.Y)
		{
			//Primary direction
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
				OutBuildingFootprint.AddPoint(FVector(NewX, StartLoc.Y, StartLoc.Z), FIntVector(x, 0, 0));
			}

			//Secondary direction
			const FVector LastAddedPrimary = OutBuildingFootprint.Last();
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = LastAddedPrimary.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutBuildingFootprint.AddPoint(FVector(LastAddedPrimary.X, NewY, LastAddedPrimary.Z), -90.f, FIntVector(DiffUnit.X, y, 0));
			}
		}
		else
		{
			//Primary Direction
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutBuildingFootprint.AddPoint(FVector(StartLoc.X, NewY, StartLoc.Z), -90.f, FIntVector(0, y, 0));
			}

			//Secondary Direction
			const FVector LastAddedPrimary = OutBuildingFootprint.Last();
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = LastAddedPrimary.X + (GridSettings->GridCellSize * (x * -XDir));
				OutBuildingFootprint.AddPoint(FVector(NewX, LastAddedPrimary.Y, LastAddedPrimary.Z), FIntVector(x, DiffUnit.Y, 0));
			}
		}
	}
};