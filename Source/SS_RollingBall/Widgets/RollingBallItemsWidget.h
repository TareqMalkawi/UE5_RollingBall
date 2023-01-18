// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RollingBallItemsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SS_ROLLINGBALL_API URollingBallItemsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetItemText(int32 ItemsInLevel , int32 ItemsCollected);
};
