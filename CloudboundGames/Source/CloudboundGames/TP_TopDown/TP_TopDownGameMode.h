// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_TopDownGameMode.generated.h"

enum class EWeaponType : uint8;
class UWeaponSelect_Base;
class ATP_TopDownPlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStartWave, int, WaveNumber, int, EnemiesKilled, int, TotalEnemies, int,
                                              MaterialsCollected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);

UCLASS(minimalapi)
class ATP_TopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_TopDownGameMode();

	UFUNCTION(BlueprintNativeEvent)
	void SetupHUD();

	UFUNCTION(BlueprintNativeEvent)
	void ChooseWeapon();
	UFUNCTION(BlueprintNativeEvent)
	void ApplyWeapon(EWeaponType Class);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartupGame();
	
	UFUNCTION(BlueprintNativeEvent)
	void Handle_GameWon();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStartWave OnWaveStart;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnGameOver OnGameOver;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerGameOver(class ULivesComponent* livesComponent);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATP_TopDownPlayerController> PlayerController;

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	TObjectPtr<UWeaponSelect_Base> WeaponSelectWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UWeaponSelect_Base> WeaponSelectWidgetType;
	
	TObjectPtr<UUserWidget> WinWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinWidgetType;

	TObjectPtr<class UHUDWidget_Base> HUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UHUDWidget_Base> HUDWidgetType;

	TObjectPtr<UUserWidget> GameOverWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameOverWidgetType;
	
	UPROPERTY(BlueprintReadWrite, Category=Waves, meta=(AllowPrivateAccess = "true"))
	int WaveNumber = 0;
};