#pragma once

#include <Runtime/CoreUObject/Public/UObject/Object.h>

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include <Runtime/Engine/Classes/GameFramework/GridLevel/GridProjection/GridProjectionInterface.h>
#include <Runtime/Engine/Classes/GameFramework/GridLevel/GridProjection/GridProjectionSettings.h>

#include "Runtime/BuildFramework/Public/Footprint/BuildFootprint.h"

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
static TAutoConsoleVariable<int32> DrawBuildPolicyPoints(TEXT("BuildPolicy.DrawPoints"), 0, TEXT("Whether or not we draw persistant lines into the world representing underlying generated points"));
#endif //!UE_BUILD_SHIPPING

#include "BuildPolicyBase.generated.h"

class AGhost;

UCLASS(abstract, editinlinenew, hidedropdown)
class UBuildPolicyBase : public UObject 
{
	GENERATED_BODY()

public:

	UBuildPolicyBase();

	void Start(AGhost& InGhost, const UBuildInfo& InBuildInfo);
	void End();

	const FBuildFootprint* GetFootprint();
	
protected:

	virtual void GeneratePoints(FBuildFootprint& OutBuildFootprint) const PURE_VIRTUAL(UBuildPolicyBase::GeneratePoints, );

	FVector StartLoc;
	FVector CurrLoc;

	TWeakInterfacePtr<IGridProjectionInterface> ProjectionInterface;

	UPROPERTY()
	const UGridProjectionSettings* GridSettings;

	FBuildFootprint GeneratedFootprint;

	FVector Diff;
	FVector DiffUnit;

	uint16 GridCellSize;

	int16 XDir;
	int16 YDir;

private:

	void OnRoundedPositionChanged(const FVector& InNewLocation);

	UPROPERTY()
	AGhost* Ghost;

	UPROPERTY()
	const UBuildInfo* BuildInfo;
};