// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownGameMode.h"

#include "TP_TopDownPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "CloudboundGames/Characters/PlayerCharacter.h"
#include "CloudboundGames/Stats/HealthComponent.h"
#include "CloudboundGames/Stats/LivesComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "CloudboundGames/UserInterface/Widgets/HUDWidget_Base.h"
#include "CloudboundGames/UserInterface/Widgets/WeaponSelect_Base.h"

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
	UHealthComponent* healthComponent = PlayerController->PlayerPawn->FindComponentByClass<UHealthComponent>();
	ULivesComponent* lifeComponent = PlayerController->PlayerPawn->FindComponentByClass<ULivesComponent>();
	if (healthComponent && lifeComponent)
	{
		lifeComponent->SetupComponent(healthComponent);
		lifeComponent->OnAllLivesLost.AddUniqueDynamic(this, &ATP_TopDownGameMode::OnPlayerGameOver);
		
		HUDWidget->SetupHealthBar(healthComponent);
		HUDWidget->SetupLivesIndicator(lifeComponent);
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

void ATP_TopDownGameMode::OnPlayerGameOver_Implementation(ULivesComponent* livesComponent)
{
	livesComponent->OnAllLivesLost.RemoveDynamic(this, &ATP_TopDownGameMode::OnPlayerGameOver);
	
	PlayerController->UnPossess();
	GameOverWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, GameOverWidgetType, "GameOver");
	HUDWidget->RemoveFromParent();
	GameOverWidget->AddToViewport();

	OnGameOver.Broadcast();
}

void ATP_TopDownGameMode::Handle_GameWon_Implementation()
{
	// show win screen
	PlayerController->UnPossess();
	WinWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, WinWidgetType, "WinGame");
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	WinWidget->AddToViewport();
}
