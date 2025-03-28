// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "../Characters/PlayerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "Engine/LocalPlayer.h"
#include "CloudboundGames/UserInterface/HUDWidget_Base.h"

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

	ACharacter* testPawn = GetCharacter();
	APlayerCharacter* TopDownCharacter = Cast<APlayerCharacter, ACharacter>(testPawn);
	if (!TopDownCharacter)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find a Character!"), *GetNameSafe(this));
		return;
	}
		
	// Setup movement events.
	EnhancedInputComponent->BindAction(HorizontalMovementAction, ETriggerEvent::Triggered, TopDownCharacter, &APlayerCharacter::OnHorizontalMovementTriggered);
	TopDownCharacter->MoveHorizontalActionBinding = &EnhancedInputComponent->BindActionValue(HorizontalMovementAction);
	EnhancedInputComponent->BindAction(VerticalMovementAction, ETriggerEvent::Triggered, TopDownCharacter, &APlayerCharacter::OnVerticalMovementTriggered);
	TopDownCharacter->MoveVerticalActionBinding = &EnhancedInputComponent->BindActionValue(VerticalMovementAction);

	EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, TopDownCharacter, &APlayerCharacter::OnRollTriggered);

	HUDWidget = CreateWidget<UHUDWidget_Base, ATP_TopDownPlayerController*>(this, HUDWidgetType, "HUD");
	
	// Setup Health Events
	if (UHealthComponent* healthComponent = TopDownCharacter->FindComponentByClass<UHealthComponent>())
	{
		healthComponent->OnKilled.AddUniqueDynamic(this, &ATP_TopDownPlayerController::OnPlayerKilled);
		HUDWidget->SetupHealthBar(healthComponent);
	}
	
	HUDWidget->AddToViewport();
}

void ATP_TopDownPlayerController::OnPlayerKilled_Implementation(UHealthComponent* healthComponent)
{
	healthComponent->OnKilled.RemoveDynamic(this, &ATP_TopDownPlayerController::OnPlayerKilled);
	
	// Stop possessing the player.
	UnPossess();

	GameOverWidget = CreateWidget<UUserWidget, ATP_TopDownPlayerController*>(this, GameOverWidgetType, "GameOver");
	HUDWidget->RemoveFromParent();
	GameOverWidget->AddToViewport();
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
