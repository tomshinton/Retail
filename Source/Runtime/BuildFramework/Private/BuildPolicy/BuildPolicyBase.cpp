#include "Runtime/BuildFramework/Public/BuildPolicy/BuildPolicyBase.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

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
{

}

void UBuildPolicyBase::Start()
{
	if (IGridProjectionInterface* Interface = IGridProjectionInterface::Get(*this))
	{
		ProjectionInterface = *Interface;

		Interface->GetOnRoundedPositionChanged().AddWeakLambda(this, [this](const FVector& InNewLoc, const FVector& InOldLoc)
		{
			OnRoundedPositionChanged(InNewLoc);
		});

		StartLoc = Interface->GetRoundedPositionUnderMouse();
		CurrLoc = StartLoc;

		GeneratePoints(GeneratedFootprint);
	}
}

void UBuildPolicyBase::End()
{
	if (ProjectionInterface.IsValid())
	{
		ProjectionInterface->GetOnRoundedPositionChanged().RemoveAll(this);
	}
}

void UBuildPolicyBase::OnRoundedPositionChanged(const FVector& InNewLocation)
{
	GeneratedFootprint.Reset();

	CurrLoc = InNewLocation;

	Diff = StartLoc - CurrLoc;
	GridCellSize = GridSettings->GridCellSize;

	DiffUnit = FVector::Abs(Diff / GridCellSize);
	GeneratedFootprint.Extent = FIntVector(DiffUnit);

	XDir = FMath::Sign(Diff.X);
	YDir = FMath::Sign(Diff.Y);

	GeneratePoints(GeneratedFootprint);

#if !UE_BUILD_SHIPPING
	if (DrawBuildPolicyPoints.GetValueOnAnyThread())
	{
		GeneratedFootprint.Visualise(*GetWorld(), static_cast<float>(GridSettings->GridCellSize));
	}
#endif //!UE_BUILD_SHIPPING
}