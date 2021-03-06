#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

#include "Runtime/BuildFramework/Public/Ghost/Ghost.h"

UBuildPolicyBase::UBuildPolicyBase() 
	: StartLoc(FVector::ZeroVector)
	, CurrLoc(FVector::ZeroVector)
	, ProjectionInterface()
	, GridSettings(GetDefault<UGridProjectionSettings>())
	, GeneratedFootprint()
	, Diff(FVector::ZeroVector)
	, DiffUnit(FVector::ZeroVector)
	, GridCellSize(GridSettings->GridCellSize)
	, XDir(0)
	, YDir(0)
	, Ghost(nullptr)
{

}

void UBuildPolicyBase::Start(AGhost& InGhost, const UBuildInfo& InBuildInfo)
{
	BuildInfo = &InBuildInfo;
	Ghost = &InGhost;

	if (IGridProjectionInterface* Interface = IGridProjectionInterface::Get(*this))
	{
		ProjectionInterface = *Interface;

		Interface->GetOnRoundedPositionChanged().AddWeakLambda(this, [this](const FVector& InNewLoc, const FVector& InOldLoc)
		{
			OnRoundedPositionChanged(InNewLoc);
		});

		StartLoc = Interface->GetRoundedPositionUnderMouse();
		CurrLoc = StartLoc;

		OnRoundedPositionChanged(StartLoc);
	}
}

void UBuildPolicyBase::End()
{
	if (ProjectionInterface.IsValid())
	{
		ProjectionInterface->GetOnRoundedPositionChanged().RemoveAll(this);
	}

	GeneratedFootprint.Reset(BuildInfo);
	Ghost->Reset();
}

void UBuildPolicyBase::Cancel()
{
	if (ProjectionInterface.IsValid())
	{
		ProjectionInterface->GetOnRoundedPositionChanged().RemoveAll(this);
	}

	GeneratedFootprint.Reset(BuildInfo);
	Ghost->Reset();
}

const FBuildFootprint* UBuildPolicyBase::GetFootprint()
{
	return &GeneratedFootprint;
}

void UBuildPolicyBase::OnRoundedPositionChanged(const FVector& InNewLocation)
{
	GeneratedFootprint.Reset(BuildInfo);

	CurrLoc = InNewLocation;

	Diff = StartLoc - CurrLoc;
	GridCellSize = GridSettings->GridCellSize;

	DiffUnit = FVector::Abs(Diff / GridCellSize);
	GeneratedFootprint.Extent = FIntVector(DiffUnit);

	XDir = FMath::Sign(Diff.X);
	YDir = FMath::Sign(Diff.Y);

	GeneratedFootprint.XDir = XDir;
	GeneratedFootprint.YDir = YDir;

	GeneratePoints(GeneratedFootprint);
	GeneratedFootprint.TryAlignCornerBridges();

	Ghost->UpdateFootprint(GeneratedFootprint);

#if !UE_BUILD_SHIPPING
	if (DrawBuildPolicyPoints.GetValueOnAnyThread())
	{
		GeneratedFootprint.Visualise(*GetWorld(), static_cast<float>(GridSettings->GridCellSize));
	}
#endif //!UE_BUILD_SHIPPING
}