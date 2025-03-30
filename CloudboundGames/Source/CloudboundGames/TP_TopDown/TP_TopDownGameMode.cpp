// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownGameMode.h"

#include "TP_TopDownPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "CloudboundGames/Waves/WaveManager_Base.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATP_TopDownGameMode::ATP_TopDownGameMode()
{
	
}

void ATP_TopDownGameMode::Handle_GameWon_Implementation()
{
	WaveManager->OnGameWon.RemoveDynamic(this, &ATP_TopDownGameMode::Handle_GameWon);

	// show win screen
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	WinWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, WinWidgetType, "WinGame");
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	WinWidget->AddToViewport();
}

void ATP_TopDownGameMode::BeginPlay()
{
	Super::BeginPlay();

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaveManager_Base::StaticClass());
	
	WaveManager = Cast<AWaveManager_Base, AActor>(actor);
	if (WaveManager)
	{
		WaveManager->OnGameWon.AddDynamic(this, &ATP_TopDownGameMode::Handle_GameWon);
	}
}
