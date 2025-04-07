// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeIcon.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API ULifeIcon : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ActiveImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> InactiveImage;

	void SetActive(bool Active);
};
