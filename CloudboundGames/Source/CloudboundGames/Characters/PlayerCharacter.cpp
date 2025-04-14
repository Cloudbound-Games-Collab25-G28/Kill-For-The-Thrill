// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "CloudboundGames/Movement/DodgeRollComponent.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter() : ACharacterBase()
{
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

	DodgeRollComponent = CreateDefaultSubobject<UDodgeRollComponent>(TEXT("DodgeRollComp"));
	DodgeRollComponent->Character = this;
	
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent = FindComponentByClass<UHealthComponent>();
	DodgeRollComponent->HealthComp = HealthComponent;
}

void APlayerCharacter::OnHorizontalMovementTriggered_Implementation()
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRot);
	AddMovementInput(RightVector, MoveHorizontalActionBinding->GetValue().Get<float>());
}

void APlayerCharacter::OnVerticalMovementTriggered_Implementation()
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlRot);
	AddMovementInput(ForwardVector, MoveVerticalActionBinding->GetValue().Get<float>());
}