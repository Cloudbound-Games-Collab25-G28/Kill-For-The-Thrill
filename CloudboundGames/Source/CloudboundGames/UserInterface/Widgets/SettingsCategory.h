// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsCategory.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API USettingsCategory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetToDefaults();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SaveSettings();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadSettings();
};
