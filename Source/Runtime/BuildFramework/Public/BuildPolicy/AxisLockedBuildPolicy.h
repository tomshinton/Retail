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

	TArray<FVector> GeneratePoints() const override
	{
		TArray<FVector> NewPoints;

		const FVector Diff = StartLoc - CurrLoc;
		const uint16 GridCellSize = GridSettings->GridCellSize;

		const FVector DiffUnit = FVector::Abs(Diff / GridCellSize);

		const int8 XDir = FMath::Sign(Diff.X);
		const int8 YDir = FMath::Sign(Diff.Y);

		if (DiffUnit.X > DiffUnit.Y)
		{
			for (uint8 x = 0; x <= DiffUnit.X; x++)
			{
				const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
				NewPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
			}
		}
		else
		{
			for (uint8 y = 0; y <= DiffUnit.Y; y++)
			{
				const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
				NewPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
			}
		}

		return NewPoints;
	}
};