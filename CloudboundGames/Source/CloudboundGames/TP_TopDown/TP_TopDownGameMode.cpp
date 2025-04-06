// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownGameMode.h"

#include "TP_TopDownPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "CloudboundGames/UserInterface/HUDWidget_Base.h"
#include "CloudboundGames/UserInterface/WeaponSelect_Base.h"

ATP_TopDownGameMode::ATP_TopDownGameMode()
{
	
}

void ATP_TopDownGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerController = Cast<ATP_TopDownPlayerController, APlayerController>(NewPlayer);
	
	if (HUDWidgetType)
	{
		SetupHUD();
	}
	
	ChooseWeapon();
}

void ATP_TopDownGameMode::SetupHUD_Implementation()
{
	HUDWidget = CreateWidget<UHUDWidget_Base, APlayerController*>(PlayerController, HUDWidgetType, "HUD");

	// Setup Health Events
	if (UHealthComponent* healthComponent = PlayerController->GetPawn()->FindComponentByClass<UHealthComponent>())
	{
		healthComponent->OnKilled.AddUniqueDynamic(this, &ATP_TopDownGameMode::OnPlayerKilled);
		HUDWidget->SetupHealthBar(healthComponent);
	}

	HUDWidget->SetupWaveIndicator(this);
	
	HUDWidget->AddToViewport();
}

void ATP_TopDownGameMode::ChooseWeapon_Implementation()
{
	// show Weapon Select
	WeaponSelectWidget = CreateWidget<UWeaponSelect_Base, APlayerController*>(PlayerController, WeaponSelectWidgetType, "WeaponSelect");
	WeaponSelectWidget->AddToViewport();

	WeaponSelectWidget->SelectWeapon.AddDynamic(this, &ATP_TopDownGameMode::ApplyWeapon);
}

void ATP_TopDownGameMode::ApplyWeapon_Implementation(EWeaponType WeaponType)
{
	WeaponSelectWidget->SelectWeapon.RemoveDynamic(this, &ATP_TopDownGameMode::ApplyWeapon);

	WeaponSelectWidget->RemoveFromParent();

	StartupGame();
}

void ATP_TopDownGameMode::StartupGame_Implementation()
{
}

void ATP_TopDownGameMode::OnPlayerKilled_Implementation(class UHealthComponent* healthComponent)
{
	healthComponent->OnKilled.RemoveDynamic(this, &ATP_TopDownGameMode::OnPlayerKilled);

	DisableInput(PlayerController);
	GameOverWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, GameOverWidgetType, "GameOver");
	HUDWidget->RemoveFromParent();
	GameOverWidget->AddToViewport();
}

void ATP_TopDownGameMode::Handle_GameWon_Implementation()
{
	// show win screen
	WinWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, WinWidgetType, "WinGame");
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	WinWidget->AddToViewport();
}
