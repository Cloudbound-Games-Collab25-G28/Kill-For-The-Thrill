// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget_Base.h"

#include "TextProgressBar.h"
#include "WaveIndicator.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "CloudboundGames/TP_TopDown/TP_TopDownGameMode.h"

class ATP_TopDownGameMode;

void UHUDWidget_Base::NativeConstruct()
{
	Super::NativeConstruct();
}


void UHUDWidget_Base::SetupHealthBar(UHealthComponent* healthComponent)
{
	HealthBar->UpdateValue(healthComponent->MaxHealth, healthComponent->MaxHealth);
	healthComponent->OnHealthChanged.AddDynamic(this, &UHUDWidget_Base::UpdateHealthBar);
}

void UHUDWidget_Base::UpdateHealthBar_Implementation(UHealthComponent* HealthComponent)
{
	HealthBar->UpdateValue(HealthComponent->Health, HealthComponent->MaxHealth);
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