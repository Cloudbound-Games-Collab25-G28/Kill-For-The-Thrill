// Fill out your copyright notice in the Description page of Project Settings.


#include "LivesCounter.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "LifeIcon.h"

void ULivesCounter::CreateLivesWidgets_Implementation(int numToCreate)
{
	for (int i = 0; i < numToCreate; i++)
	{
		ULifeIcon* widget = CreateWidget<ULifeIcon, APlayerController*>(GetOwningPlayer(), LivesIconWidget, "Icon");
		UHorizontalBoxSlot* slot = HorizontalBox->AddChildToHorizontalBox(widget);
		slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		slot->SetPadding(SlotPadding);

		LivesIcons.Add(widget);
	}
}

void ULivesCounter::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void ULivesCounter::UpdateLivesVisual_Implementation(int currentLives)
{
	int index = 0;
	for (ULifeIcon* icon : LivesIcons)
	{
		icon->SetActive(true);
		if (index < currentLives)
		{
			icon->SetActive(true);
		}
		else
		{
			icon->SetActive(false);
		}
		index++;
	}
}

void ULivesCounter::UpdateLives(int totalLives, int currentLives)
{
	if (totalLives > LivesDisplayed)
	{
		CreateLivesWidgets(totalLives - LivesDisplayed);
		LivesDisplayed = totalLives;
	}

	UpdateLivesVisual(currentLives);
}
