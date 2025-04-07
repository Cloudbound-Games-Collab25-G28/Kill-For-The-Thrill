// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveIndicator.h"

void UWaveIndicator::UpdateValue(int waveNumber)
{
	if (WaveBrushes.Contains(waveNumber))
	{
		WaveImage->SetBrush(WaveBrushes[waveNumber]);
	}
	else
	{
		WaveImage->SetBrush(DefaultImage);
	}
}
