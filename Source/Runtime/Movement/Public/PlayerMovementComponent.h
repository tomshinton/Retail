// Tom Shinton - Retail 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "PlayerMovementComponent.generated.h"

class USpringArmComponent;

struct FCombinedMove
{
public:

	FCombinedMove()
		: Forward(0.f)
		, Right(0.f)
		, Rotate(0.f)
	{};

	FVector Get() const 
	{
		return FVector(Forward, Right, 0.f);
	}

	float Forward;
	float Right;

	float Rotate;
};

UCLASS(MinimalAPI, Within=Pawn)
class UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPlayerMovementComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MinZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MaxZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float RotateSpeed;

protected:

	//UActorComponent
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
	//~UActorComponent

private:

	UPROPERTY()
	USpringArmComponent* CameraArm;

	FCombinedMove CombinedMove;

	void MoveForward(const float InStrength);
	void MoveRight(const float InStrength);

	void Rotate(const float InStrength);

	void ZoomIn();
	void ZoomOut();

	void AlterSpringArmLength(const float InAmount);
};
