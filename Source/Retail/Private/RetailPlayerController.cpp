// Tom Shinton - Retail 2020

#include "Retail/Public/RetailPlayerController.h"

#if !UE_BUILD_SHIPPING
#include "Retail/Public/RetailCheatManager.h"
#endif //!UE_BUILD_SHIPPING

ARetailPlayerController::ARetailPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

#if !UE_BUILD_SHIPPING
	CheatClass = URetailCheatManager::StaticClass();
#endif //!UE_BUILD_SHIPPING
}

void ARetailPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;

	InputMode
		.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways)
		.SetHideCursorDuringCapture(false)
		.SetWidgetToFocus(nullptr)
		.SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);

	SetInputMode(InputMode);

#if !UE_BUILD_SHIPPING
	EnableCheats();
#endif //!UE_BUILD_SHIPPING
}
