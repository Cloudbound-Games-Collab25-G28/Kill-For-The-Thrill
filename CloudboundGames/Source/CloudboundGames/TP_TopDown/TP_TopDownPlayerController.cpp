// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "../Characters/PlayerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "CloudboundGames/Movement/DodgeRollComponent.h"
#include "CloudboundGames/UserInterface/Widgets/HUDWidget_Base.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATP_TopDownPlayerController::ATP_TopDownPlayerController()
{
}

void ATP_TopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATP_TopDownPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		return;
	}
	
	APlayerCharacter* TopDownCharacter = Cast<APlayerCharacter, ACharacter>(GetCharacter());
	if (!TopDownCharacter)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find a Character!"), *GetNameSafe(this));
		return;
	}

	PlayerPawn = TopDownCharacter;
	// Setup movement events.
	EnhancedInputComponent->BindAction(HorizontalMovementAction, ETriggerEvent::Triggered, TopDownCharacter, &APlayerCharacter::OnHorizontalMovementTriggered);
	TopDownCharacter->MoveHorizontalActionBinding = &EnhancedInputComponent->BindActionValue(HorizontalMovementAction);
	EnhancedInputComponent->BindAction(VerticalMovementAction, ETriggerEvent::Triggered, TopDownCharacter, &APlayerCharacter::OnVerticalMovementTriggered);
	TopDownCharacter->MoveVerticalActionBinding = &EnhancedInputComponent->BindActionValue(VerticalMovementAction);

	EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, TopDownCharacter->DodgeRollComponent, &UDodgeRollComponent::OnRollTriggered);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ATP_TopDownPlayerController::OnPauseTriggered);
}

void ATP_TopDownPlayerController::OnPauseTriggered()
{
	OnPauseGame.Broadcast();
}

void ATP_TopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
