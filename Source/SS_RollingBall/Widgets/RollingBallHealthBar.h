// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RollingBallHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class SS_ROLLINGBALL_API URollingBallHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetHealthBarValue(float HealthValue);
	
};
