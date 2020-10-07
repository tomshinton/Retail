// Tom Shinton - Retail 2020

#include "Retail/Public/RetailPlayer.h"

#include <Runtime/BuildFramework/Public/BuildComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Movement/Public/PlayerMovementComponent.h>

namespace RetailPlayerPrivate
{
	const FName MovementComponentName = TEXT("MovementComponent");
	const FName SpringArmComponentName = TEXT("CameraArm");
	const FName CameraComponentName = TEXT("Camera");
	const FName PlayerRootName = TEXT("PlayerRoot");
	const FName BuildComponentName = TEXT("BuildComponent");
}

ARetailPlayer::ARetailPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, PlayerRoot(ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, RetailPlayerPrivate::PlayerRootName))
	, PlayerMovementComponent(ObjectInitializer.CreateDefaultSubobject<UPlayerMovementComponent>(this, RetailPlayerPrivate::MovementComponentName))
	, BuildComponent(ObjectInitializer.CreateDefaultSubobject<UBuildComponent>(this, RetailPlayerPrivate::BuildComponentName))
	, CameraArm(ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, RetailPlayerPrivate::SpringArmComponentName))
	, Camera(ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, RetailPlayerPrivate::CameraComponentName))
{
	SetRootComponent(PlayerRoot);
	CameraArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(CameraArm);

	CameraArm->bDoCollisionTest = false;
}