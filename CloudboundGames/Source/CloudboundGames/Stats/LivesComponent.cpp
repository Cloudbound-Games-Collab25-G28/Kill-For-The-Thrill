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

void ULivesComponent::RevivePlayer_Implementation(UHealthComponent* HealthComponent)
{
	HealthComponent->SetHealth(HealthComponent->MaxHealth);
}

void ULivesComponent::OnKilled_Implementation(UHealthComponent* HealthComponent)
{
	CurrentLives--;
	OnLifeLost.Broadcast(this);

	if (CurrentLives > 0)
	{
		RevivePlayer(HealthComponent);
		return;
	}

	HealthComponent->OnKilled.RemoveDynamic(this, &ULivesComponent::OnKilled);

	OnAllLivesLost.Broadcast(this);
}
