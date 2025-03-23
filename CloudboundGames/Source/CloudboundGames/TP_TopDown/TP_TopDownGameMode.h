// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_TopDownGameMode.generated.h"

class AWaveManager_Base;

UCLASS(minimalapi)
class ATP_TopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_TopDownGameMode();

	UFUNCTION(BlueprintNativeEvent)
	void Handle_GameWon();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinWidgetType;

private:
	TObjectPtr<AWaveManager_Base> WaveManager;

	TObjectPtr<UUserWidget> WinWidget;
};