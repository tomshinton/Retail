#pragma once

#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"

#include "RoomBuildPolicy.generated.h"

UCLASS()
class URoomBuildPolicy : public UBuildPolicyBase
{
	GENERATED_BODY()

public:

	URoomBuildPolicy()
	{};

	TArray<FVector> GeneratePoints() const override
	{
		TArray<FVector> NewPoints;

		const FVector Diff = StartLoc - CurrLoc;
		const uint16 GridCellSize = GridSettings->GridCellSize;

		const FVector DiffUnit = FVector::Abs(Diff / GridCellSize);

		const int8 XDir = FMath::Sign(Diff.X);
		const int8 YDir = FMath::Sign(Diff.Y);

		//Primary direction
		const float YOffset = (DiffUnit.Y * GridSettings->GridCellSize) * -YDir;
		for (uint8 x = 0; x <= DiffUnit.X; x++)
		{
			const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
			NewPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
			NewPoints.AddUnique(FVector(NewX, StartLoc.Y + YOffset, StartLoc.Z));
		}

		//Secondary direction
		const float XOffset = (DiffUnit.X * GridSettings->GridCellSize) * -XDir;
		for (uint8 y = 0; y <= DiffUnit.Y; y++)
		{
			const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
			NewPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
			NewPoints.AddUnique(FVector(StartLoc.X + XOffset, NewY, StartLoc.Z));
		}

		return NewPoints;
	}
};
