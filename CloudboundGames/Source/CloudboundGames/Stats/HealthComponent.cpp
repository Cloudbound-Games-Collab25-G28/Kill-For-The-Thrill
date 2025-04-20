// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	
}

void UHealthComponent::SetHealth_Implementation(float NewHealth)
{
}

void UHealthComponent::SetInvincibility_Implementation(bool newValue)
{
	this->isInvincible = isInvincible;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}