// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "WaveIndicator.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API UWaveIndicator : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> WaveImage;

public:

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush DefaultImage;

	UPROPERTY(EditDefaultsOnly)
	TMap<int, FSlateBrush> WaveBrushes;

	UFUNCTION(BlueprintCallable)
	void UpdateValue(int waveNumber);
};
