// Tom Shinton - Retail 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Pawn.h>

#include "RetailPlayer.generated.h"

class UCameraComponent;
class UPlayerMovementComponent;
class USceneComponent;
class USpringArmComponent;

UCLASS()
class ARetailPlayer : public APawn
{
	GENERATED_BODY()

public:

	ARetailPlayer(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	USceneComponent* PlayerRoot;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;
};
