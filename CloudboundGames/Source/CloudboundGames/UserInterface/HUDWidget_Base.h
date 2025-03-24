// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget_Base.generated.h"

class UTextProgressBar;
class UHealthComponent;
class UProgressBar;
/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API UHUDWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void SetupHealthBar(UHealthComponent* healthComp);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateHealthBar(UHealthComponent* HealthComponent);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextProgressBar> HealthBar;
};
