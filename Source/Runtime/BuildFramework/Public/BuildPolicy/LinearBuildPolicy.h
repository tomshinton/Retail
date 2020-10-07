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

	virtual void GeneratePoints(TArray<FVector>& OutGeneratedPoints) const override
	{
		if (DiffUnit.X > DiffUnit.Y)
		{
			//Primary direction
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
				OutGeneratedPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
			}

			//Secondary direction
			const FVector LastAddedPrimary = OutGeneratedPoints.Last();
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = LastAddedPrimary.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutGeneratedPoints.AddUnique(FVector(LastAddedPrimary.X, NewY, LastAddedPrimary.Z));
			}
		}
		else
		{
			//Primary Direction
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
				OutGeneratedPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
			}

			//Secondary Direction
			const FVector LastAddedPrimary = OutGeneratedPoints.Last();
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = LastAddedPrimary.X + (GridSettings->GridCellSize * (x * -XDir));
				OutGeneratedPoints.AddUnique(FVector(NewX, LastAddedPrimary.Y, LastAddedPrimary.Z));
			}
		}
	}
};