// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollingBallPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SS_ROLLINGBALL_API ARollingBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollingBallPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Global Settings")
	float HorizontalForce = 700.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Global Settings")
	float MaxJumpImpulse = 500.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Global Settings")
	float JumpImpulse = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Global Settings")
	int32 MaxJumpCounter = 1;


private:
	
	void MoveRight(float value);
	void Jump();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit );

	int32 JumpCounter = 0;
};
