// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeIcon.h"

#include "Components/Image.h"

void ULifeIcon::SetActive(bool Active)
{
	if (Active)
	{
		ActiveImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ActiveImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
