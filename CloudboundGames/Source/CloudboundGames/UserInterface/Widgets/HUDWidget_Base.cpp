// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget_Base.h"

#include "CloudboundGames/UserInterface/Elements/TextProgressBar.h"
#include "CloudboundGames/UserInterface/Elements/WaveIndicator.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "CloudboundGames/Stats/LivesComponent.h"
#include "CloudboundGames/TP_TopDown/TP_TopDownGameMode.h"
#include "CloudboundGames/UserInterface/Elements/LivesCounter.h"

void UHUDWidget_Base::NativeConstruct()
{
	Super::NativeConstruct();
}


void UHUDWidget_Base::SetupHealthBar(UHealthComponent* HealthComponent)
{
	HealthBar->UpdateValue(HealthComponent->GetMaxHealth(), HealthComponent->GetMaxHealth());
	HealthComponent->OnHealthChanged.AddDynamic(this, &UHUDWidget_Base::UpdateHealthBar);
}

void UHUDWidget_Base::UpdateHealthBar_Implementation(UHealthComponent* HealthComponent)
{
	HealthBar->UpdateValue(HealthComponent->GetHealth(), HealthComponent->GetMaxHealth());
}

void UHUDWidget_Base::SetupLivesIndicator(class ULivesComponent* LivesComponent)
{
	LivesCounter->UpdateLives(LivesComponent->GetMaxLives(), LivesComponent->GetLives());
	LivesComponent->OnLivesChanged.AddDynamic(this, &UHUDWidget_Base::UpdatesLives);
}

void UHUDWidget_Base::UpdatesLives_Implementation(ULivesComponent* LivesComponent)
{
	LivesCounter->UpdateLives(LivesComponent->GetMaxLives(), LivesComponent->GetLives());
}

void UHUDWidget_Base::SetupWaveIndicator(ATP_TopDownGameMode* WaveManager)
{
	WaveIndicator->UpdateValue(1);
	WaveManager->OnWaveStart.AddDynamic(this, &UHUDWidget_Base::UpdateWaveIndicator);
}

void UHUDWidget_Base::UpdateWaveIndicator_Implementation(int WaveNumber, int EnemiesKilled, int TotalEnemies, int MaterialsCollected)
{
	WaveIndicator->UpdateValue(WaveNumber);
}