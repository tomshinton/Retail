#pragma once

#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"

#include <Runtime/Engine/Public/DrawDebugHelpers.h>

#include "LinearBuildPolicy.generated.h"

UCLASS()
class ULinearBuildPolicy : public UBuildPolicyBase
{
	GENERATED_BODY()

public:

	ULinearBuildPolicy()
	{};


	virtual TArray<FVector> GeneratePoints() const override
	{
		if (UWorld* World = GetWorld())
		{
			TArray<FVector> NewPoints;

			const FVector Diff = StartLoc - CurrLoc;
			const uint16 GridCellSize = GridSettings->GridCellSize;

			const FVector DiffUnit = FVector::Abs(Diff / GridCellSize);

			const int8 XDir = FMath::Sign(Diff.X);
			const int8 YDir = FMath::Sign(Diff.Y);

			if (DiffUnit.X > DiffUnit.Y)
			{
				//Primary direction
				for (uint8 x = 0; x <= DiffUnit.X; x++)
				{
					const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
					NewPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
				}

				//Secondary direction
				const FVector LastAddedPrimary = NewPoints.Last();
				for (uint8 y = 0; y <= DiffUnit.Y; y++)
				{
					const float NewY = LastAddedPrimary.Y + (GridSettings->GridCellSize * (y * -YDir));
					NewPoints.AddUnique(FVector(LastAddedPrimary.X, NewY, LastAddedPrimary.Z));
				}
			}
			else
			{
				//Primary Direction
				for (uint8 y = 0; y <= DiffUnit.Y; y++)
				{
					const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
					NewPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
				}

				//Secondary Direction
				const FVector LastAddedPrimary = NewPoints.Last();
				for (uint8 x = 0; x <= DiffUnit.X; x++)
				{
					const float NewX = LastAddedPrimary.X + (GridSettings->GridCellSize * (x * -XDir));
					NewPoints.AddUnique(FVector(NewX, LastAddedPrimary.Y, LastAddedPrimary.Z));
				}
			}

			return NewPoints;
		}

		return TArray<FVector>();
	}
};