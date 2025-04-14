// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeRollComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UDodgeRollComponent::UDodgeRollComponent()
{
	bCanRoll = true;
}


void UDodgeRollComponent::OnRollTriggered_Implementation()
{
	if (bCanRoll)
	{
		bCanRoll = false;
		RollPlayer();
		
		FTimerHandle RollTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(RollTimerHandle, this, &UDodgeRollComponent::ResetRollCooldown, RollCooldownTime, false);
	}
}

void UDodgeRollComponent::RollPlayer_Implementation()
{
	GetOwner()->AddActorWorldOffset(GetLaunchVelocity());

	if (bool isMotionActive = Character->GetCharacterMovement()->IsActive(); !isMotionActive)
	{
		Character->GetCharacterMovement()->Activate();
	}
	
	Character->LaunchCharacter(GetLaunchVelocity(), false, false);
}

void UDodgeRollComponent::ResetRollCooldown_Implementation()
{
	bCanRoll = true;
}

FVector UDodgeRollComponent::GetLaunchVelocity_Implementation() const
{
	FVector Velocity = GetOwner()->GetVelocity();
	if (Velocity.SizeSquared() > 0.f)
	{
		Velocity.Normalize();
		return Velocity * RollSpeed;
	}
	
	return RollSpeed * GetOwner()->GetActorForwardVector();
}