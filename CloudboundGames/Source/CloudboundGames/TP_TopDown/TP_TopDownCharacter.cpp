// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownCharacter.h"

#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ATP_TopDownCharacter::ATP_TopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ATP_TopDownCharacter::OnHorizontalMovementTriggered()
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRot);
	AddMovementInput(RightVector, MoveHorizontalActionBinding->GetValue().Get<float>());
}

void ATP_TopDownCharacter::OnVerticalMovementTriggered()
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlRot);
	AddMovementInput(ForwardVector, MoveVerticalActionBinding->GetValue().Get<float>());
}

void ATP_TopDownCharacter::OnRollTriggered()
{
	if (bCanRoll)
	{
		bCanRoll = false;
		LaunchCharacter(GetLaunchVelocity(), false, false);
		
		FTimerHandle RollTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(RollTimerHandle, this, &ATP_TopDownCharacter::ResetRollCooldown, RollCooldownTime, false);
	}
}

void ATP_TopDownCharacter::ResetRollCooldown()
{
	bCanRoll = true;
}

FVector ATP_TopDownCharacter::GetLaunchVelocity_Implementation() const
{
	return GetLaunchVelocity();
}
