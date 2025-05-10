// Fill out your copyright notice in the Description page of Project Settings.


#include "LivesComponent.h"

#include "HealthComponent.h"


// Sets default values for this component's properties
ULivesComponent::ULivesComponent()
{
	
}

void ULivesComponent::SetupComponent(UHealthComponent* HealthComponent)
{
	CurrentLives = MaxLives;
	
	HealthComponent->OnKilled.AddDynamic(this, &ULivesComponent::OnKilled);
}

void ULivesComponent::SetLives_Implementation(int lives)
{
	CurrentLives = lives;
	OnLivesChanged.Broadcast(this);
}

void ULivesComponent::SetMaxLives_Implementation(int max)
{
	MaxLives = max;
	OnLivesChanged.Broadcast(this);
}

int ULivesComponent::GetMaxLives_Implementation() const
{
	return MaxLives;
}

int ULivesComponent::GetLives_Implementation() const
{
	return CurrentLives;
}

void ULivesComponent::RevivePlayer_Implementation(UHealthComponent* HealthComponent)
{
	HealthComponent->SetHealth(HealthComponent->MaxHealth);
}

void ULivesComponent::OnKilled_Implementation(UHealthComponent* HealthComponent)
{
	CurrentLives--;
	OnLivesChanged.Broadcast(this);
	OnLifeLost.Broadcast(this);

	if (CurrentLives > 0)
	{
		RevivePlayer(HealthComponent);
		return;
	}

	HealthComponent->OnKilled.RemoveDynamic(this, &ULivesComponent::OnKilled);

	OnAllLivesLost.Broadcast(this);
}
