// Fill out your copyright notice in the Description page of Project Settings.


#include "TextProgressBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTextProgressBar::UpdateValue(float newValue, float maxValue)
{
	Bar->SetPercent(newValue/maxValue);
	ValueText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), (int)newValue, (int)maxValue)));
}