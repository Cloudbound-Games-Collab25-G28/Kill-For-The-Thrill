// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_TopDownGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStartWave, int, WaveNumber, int, EnemiesKilled, int, TotalEnemies, int, MaterialsCollected);

UCLASS(minimalapi)
class ATP_TopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_TopDownGameMode();
	
	UFUNCTION(BlueprintNativeEvent)
	void Handle_GameWon();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStartWave OnWaveStart;

private:
	
	TObjectPtr<UUserWidget> WinWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinWidgetType;
	
	UPROPERTY(BlueprintReadWrite, Category=Waves, meta=(AllowPrivateAccess = "true"))
	int WaveNumber = 0;
};