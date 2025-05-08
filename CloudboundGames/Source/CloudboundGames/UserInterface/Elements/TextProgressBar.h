// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextProgressBar.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS(BlueprintType)
class CLOUDBOUNDGAMES_API UTextProgressBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateValue(float newValue, float maxValue);


};