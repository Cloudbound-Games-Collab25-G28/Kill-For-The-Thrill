// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget_Base.h"

#include "TextProgressBar.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "Components/ProgressBar.h"

void UHUDWidget_Base::NativeConstruct()
{
	Super::NativeConstruct();
}


void UHUDWidget_Base::SetupHealthBar(UHealthComponent* healthComponent)
{
	healthComponent->OnHealthChanged.AddDynamic(this, &UHUDWidget_Base::UpdateHealthBar);
	HealthBar->UpdateValue(healthComponent->Health, healthComponent->MaxHealth);
}

void UHUDWidget_Base::UpdateHealthBar_Implementation(UHealthComponent* HealthComponent)
{
	HealthBar->UpdateValue(HealthComponent->Health, HealthComponent->MaxHealth);
}
