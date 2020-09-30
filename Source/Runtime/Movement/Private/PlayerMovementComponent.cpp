// Tom Shinton - Retail 2020

#include "Runtime/Movement/Public/PlayerMovementComponent.h"

#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>

DEFINE_LOG_CATEGORY_STATIC(PlayerMovementComponent, Log, All)

namespace PlayerMovementBindings
{
	const FName ForwardBinding = TEXT("Forward");
	const FName RightBinding = TEXT("Right");

	const FName RotateBinding = TEXT("Rotate");

	const FName ZoomInBinding = TEXT("ZoomIn");
	const FName ZoomOutBinding = TEXT("ZoomOut");
}

UPlayerMovementComponent::UPlayerMovementComponent()
	: MoveSpeed(100.f)
	, ZoomSpeed(100.f)
	, MinZoom(100.f)
	, MaxZoom(3000.f)
	, RotateSpeed(100.f)
	, CameraArm(nullptr)
	, CombinedMove()
{
	SetComponentTickEnabled(true);
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		CameraArm = Owner->FindComponentByClass<USpringArmComponent>();

		if (CameraArm != nullptr)
		{
			AlterSpringArmLength(MaxZoom);
		}
		else
		{
			UE_LOG(PlayerMovementComponent, Error, TEXT("Could not source CameraArm from %s!"), *Owner->GetName());
		}
	}
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AActor* Owner = GetOwner())
	{
		const FVector MoveActual = CombinedMove.Get() * (MoveSpeed * DeltaTime);
		if (MoveActual.Size() > 0.f)
		{
			const FVector OwnerLoc = Owner->GetActorLocation();

			FVector NewLocation = OwnerLoc;

			NewLocation += FVector(Owner->GetActorForwardVector() * MoveActual.X); //Apply forward
			NewLocation += FVector(Owner->GetActorRightVector() * MoveActual.Y); //Apply right

			Owner->SetActorLocation(NewLocation);
		}

		const float RotateActual = CombinedMove.Rotate * (RotateSpeed * DeltaTime);
		if (!FMath::IsNearlyZero(RotateActual))
		{
			const FRotator OwnerRot = Owner->GetActorRotation();
			const FRotator NewRot = OwnerRot + FRotator(0.f, RotateActual, 0.f);

			Owner->SetActorRotation(NewRot);
		}
	}
}

void UPlayerMovementComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	PlayerInputComponent.BindAxis(PlayerMovementBindings::ForwardBinding, this, &UPlayerMovementComponent::MoveForward);
	PlayerInputComponent.BindAxis(PlayerMovementBindings::RightBinding, this, &UPlayerMovementComponent::MoveRight);

	PlayerInputComponent.BindAxis(PlayerMovementBindings::RotateBinding, this, &UPlayerMovementComponent::Rotate);

	PlayerInputComponent.BindAction(PlayerMovementBindings::ZoomInBinding, IE_Pressed, this, &UPlayerMovementComponent::ZoomIn);
	PlayerInputComponent.BindAction(PlayerMovementBindings::ZoomOutBinding, IE_Pressed, this, &UPlayerMovementComponent::ZoomOut);
}

void UPlayerMovementComponent::MoveForward(const float InStrength)
{
	CombinedMove.Forward = InStrength;
}

void UPlayerMovementComponent::MoveRight(const float InStrength)
{
	CombinedMove.Right = InStrength;
}

void UPlayerMovementComponent::Rotate(const float InStrength)
{
	CombinedMove.Rotate = InStrength;
}

void UPlayerMovementComponent::ZoomIn()
{
	AlterSpringArmLength(-1.f);
}

void UPlayerMovementComponent::ZoomOut()
{
	AlterSpringArmLength(1.f);
}

void UPlayerMovementComponent::AlterSpringArmLength(const float InAmount)
{
	if (CameraArm != nullptr)
	{
		const float CurrentLength = CameraArm->TargetArmLength;
		const float NewLength = FMath::Clamp(CurrentLength + (ZoomSpeed * InAmount), MinZoom, MaxZoom);

		CameraArm->TargetArmLength = NewLength;
	}
	else
	{
		UE_LOG(PlayerMovementComponent, Error, TEXT("Could not alter camera arm length - could not source target arm from owning actor"));
	}
}
