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

	virtual void GeneratePoints(TArray<FVector>& OutGeneratedPoints) const override
	{
		//Primary direction
		const float YOffset = (DiffUnit.Y * GridSettings->GridCellSize) * -YDir;
		for (uint8 x = 0; x <= DiffUnit.X; x++)
		{
			const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
			OutGeneratedPoints.AddUnique(FVector(NewX, StartLoc.Y, StartLoc.Z));
			OutGeneratedPoints.AddUnique(FVector(NewX, StartLoc.Y + YOffset, StartLoc.Z));
		}

		//Secondary direction
		const float XOffset = (DiffUnit.X * GridSettings->GridCellSize) * -XDir;
		for (uint8 y = 0; y <= DiffUnit.Y; y++)
		{
			const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
			OutGeneratedPoints.AddUnique(FVector(StartLoc.X, NewY, StartLoc.Z));
			OutGeneratedPoints.AddUnique(FVector(StartLoc.X + XOffset, NewY, StartLoc.Z));
		}
	}
};
