// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LivesCounter.generated.h"

class UHorizontalBox;
class ULifeIcon;
/**
 * 
 */
UCLASS()
class CLOUDBOUNDGAMES_API ULivesCounter : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULifeIcon> LivesIconWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<ULifeIcon>> LivesIcons;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FMargin SlotPadding;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CreateLivesWidgets(int numToCreate);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateLivesVisual(int currentLives);
	
	void UpdateLives(int totalLives, int currentLives);

private:
	int LivesDisplayed = 0;
};
