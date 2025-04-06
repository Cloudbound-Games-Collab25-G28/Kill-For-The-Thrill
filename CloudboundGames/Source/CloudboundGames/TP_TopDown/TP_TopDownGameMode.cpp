// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATP_TopDownGameMode::ATP_TopDownGameMode()
{
	
}

void ATP_TopDownGameMode::Handle_GameWon_Implementation()
{
	// show win screen
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	WinWidget = CreateWidget<UUserWidget, APlayerController*>(PlayerController, WinWidgetType, "WinGame");
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	WinWidget->AddToViewport();
}
