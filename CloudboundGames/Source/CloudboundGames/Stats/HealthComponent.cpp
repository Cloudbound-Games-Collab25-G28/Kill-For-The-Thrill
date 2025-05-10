// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	
}

void UHealthComponent::SetHealth_Implementation(float NewHealth)
{
	Health = NewHealth;
	OnHealthChanged.Broadcast(this);
}

void UHealthComponent::SetInvincibility_Implementation(bool newValue)
{
	this->isInvincible = newValue;
}

float UHealthComponent::GetHealth_Implementation() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth_Implementation() const
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth_Implementation(float NewHealth)
{
	MaxHealth = NewHealth;
	OnHealthChanged.Broadcast(this);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}