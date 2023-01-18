// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SS_RollingBall/Widgets/RollingBallPauseMenu.h"
#include "RollingBallGameModeBase.generated.h"

class URollingBallHealthBar;
class URollingBallItemsWidget;
UCLASS()
class SS_ROLLINGBALL_API ARollingBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	int32 ItemsInLevel = 0;
	int32 ItemsCollected = 0;

	float Health = 0.0f;

	class ARollingBallPlayer* RollingBallPlayer;

	UPROPERTY(EditAnywhere,Category="Widgets")
	TSubclassOf<class UUserWidget> ItemWidgetClass;

	URollingBallItemsWidget* ItemWidget;

	UPROPERTY(EditAnywhere,Category="Widgets")
	TSubclassOf<class UUserWidget> HealthWidgetClass;

	URollingBallHealthBar* HealthWidget;

	UPROPERTY(EditAnywhere,Category="Widgets")
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	URollingBallPauseMenu* PauseMenuWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	float MaxHealth = 100.0f;
	
	virtual void BeginPlay() override;

	void UpdateItemText();

	void RestartCurrentLevel();

public:
	void ItemCollected();
	void UpdateHealth();
};
