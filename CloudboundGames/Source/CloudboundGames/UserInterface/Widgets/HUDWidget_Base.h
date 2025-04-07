// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget_Base.generated.h"

class UHealthComponent;
/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API UHUDWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void SetupHealthBar(UHealthComponent* HealthComponent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateHealthBar(UHealthComponent* HealthComponent);

	void SetupWaveIndicator(class ATP_TopDownGameMode* WaveManager);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWaveIndicator(int WaveNumber, int EnemiesKilled, int TotalEnemies, int MaterialsCollected);

	void SetupLivesIndicator(class ULivesComponent* LivesComponent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdatesLives(ULivesComponent* LivesComponent);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class ULivesCounter> LivesCounter;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWaveIndicator> WaveIndicator;
};
