#pragma once

#include <Runtime/CoreUObject/Public/UObject/Object.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include <Runtime/Engine/Classes/GameFramework/GridLevel/GridProjection/GridProjectionInterface.h>
#include <Runtime/Engine/Classes/GameFramework/GridLevel/GridProjection/GridProjectionSettings.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
static TAutoConsoleVariable<int32> DrawBuildPolicyPoints(TEXT("BuildPolicy.DrawPoints"), 0, TEXT("Whether or not we draw persistant lines into the world representing underlying generated points"));
#endif //!UE_BUILD_SHIPPING

#include "BuildPolicyBase.generated.h"

UCLASS(abstract, editinlinenew, hidedropdown)
class UBuildPolicyBase : public UObject 
{
	GENERATED_BODY()

public:

	UBuildPolicyBase()
		: StartLoc(FVector::ZeroVector)
		, CurrLoc(FVector::ZeroVector)
		, ProjectionInterface()
		, GridSettings(GetDefault<UGridProjectionSettings>())
	{};

	void Start()
	{
		if (IGridProjectionInterface* Interface = IGridProjectionInterface::Get(*this))
		{
			ProjectionInterface = *Interface;

			Interface->GetOnRoundedPositionChanged().AddWeakLambda(this, [this](const FVector& InNewLoc, const FVector& InOldLoc)
			{
				CurrLoc = InNewLoc;
				GeneratedPoints = GeneratePoints();

#if !UE_BUILD_SHIPPING
				if (UWorld* World = GetWorld())
				{
					if (DrawBuildPolicyPoints.GetValueOnAnyThread())
					{
						FlushPersistentDebugLines(World);

						for (const FVector& Point : GeneratedPoints)
						{
							DrawDebugSphere(World, Point, static_cast<float>(GridSettings->GridCellSize) * 0.5f, 12, FColor::White, true);
						}
					}
				}
#endif //!UE_BUILD_SHIPPING
			});

			StartLoc = Interface->GetRoundedPositionUnderMouse();
			CurrLoc = StartLoc;
		}
	}

	void End()
	{
		if (ProjectionInterface.IsValid())
		{
			ProjectionInterface->GetOnRoundedPositionChanged().RemoveAll(this);
		}
	}
	
	virtual TArray<FVector> GeneratePoints() const PURE_VIRTUAL(UBuildPolicyBase::GeneratePoints, return TArray<FVector>(););

protected:

	FVector StartLoc;
	FVector CurrLoc;

	TWeakInterfacePtr<IGridProjectionInterface> ProjectionInterface;

	UPROPERTY()
	const UGridProjectionSettings* GridSettings;

	TArray<FVector> GeneratedPoints;
};