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

	virtual void GeneratePoints(FBuildFootprint& OutBuildingFootprint) const override
	{
		//Primary direction
		const float YOffset = (DiffUnit.Y * GridSettings->GridCellSize) * -YDir;
		for (uint8 x = 0; x <= DiffUnit.X; x++)
		{
			const float NewX = StartLoc.X + (GridSettings->GridCellSize * (x * -XDir));
			OutBuildingFootprint.AddPoint(FVector(NewX, StartLoc.Y, StartLoc.Z), FIntVector(x, 0, 0));
			OutBuildingFootprint.AddPoint(FVector(NewX, StartLoc.Y + YOffset, StartLoc.Z), FIntVector(x, DiffUnit.Y, 0));
		}

		//Secondary direction
		const float XOffset = (DiffUnit.X * GridSettings->GridCellSize) * -XDir;
		for (uint8 y = 0; y <= DiffUnit.Y; y++)
		{
			const float NewY = StartLoc.Y + (GridSettings->GridCellSize * (y * -YDir));
			OutBuildingFootprint.AddPoint(FVector(StartLoc.X, NewY, StartLoc.Z), -90.f, FIntVector(0, y, 0));
			OutBuildingFootprint.AddPoint(FVector(StartLoc.X + XOffset, NewY, StartLoc.Z), -90.f, FIntVector(DiffUnit.X, y, 0));
		}
	}
};
