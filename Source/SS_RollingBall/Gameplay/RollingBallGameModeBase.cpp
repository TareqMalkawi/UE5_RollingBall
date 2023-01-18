// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallGameModeBase.h"

#include "RollingBallPlayer.h"
#include "SS_RollingBall/Items/RollingBallItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "SS_RollingBall/Widgets/RollingBallHealthBar.h"
#include "SS_RollingBall/Widgets/RollingBallItemsWidget.h"

void ARollingBallGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	// AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(),ARollingBallPlayer::StaticClass());
	// if(Player)
	// {
	// 	RollingBallPlayer = Cast<ARollingBallPlayer>(Player);
	// }
	
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ARollingBallItemBase::StaticClass(),Items);
	ItemsInLevel = Items.Num();

	if(ItemWidgetClass)
	{
		ItemWidget = Cast<URollingBallItemsWidget>(CreateWidget(GetWorld(),ItemWidgetClass));
		if(ItemWidget)
		{
			ItemWidget->AddToViewport();
			UpdateItemText();
		}
	}

	if(HealthWidgetClass)
	{
		HealthWidget = Cast<URollingBallHealthBar>(CreateWidget(GetWorld(),HealthWidgetClass));
		if(HealthWidget)
		{
			HealthWidget->AddToViewport();
			HealthWidget->SetHealthBarValue(Health);
		}
	}

	if(PauseMenuWidgetClass)
	{
		PauseMenuWidget = Cast<URollingBallPauseMenu>(CreateWidget(GetWorld(),PauseMenuWidgetClass));
		if(PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
		}
	}
}

void ARollingBallGameModeBase::UpdateItemText()
{
	ItemWidget->SetItemText(ItemsInLevel,ItemsCollected);
}


void ARollingBallGameModeBase::ItemCollected()
{
	++ItemsCollected;
	UpdateItemText();
}

void ARollingBallGameModeBase::UpdateHealth()
{
	if(Health <= 5.0f) RestartCurrentLevel();

	Health -= 10.0f;
	HealthWidget->SetHealthBarValue(Health / MaxHealth);
}
void ARollingBallGameModeBase::RestartCurrentLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
