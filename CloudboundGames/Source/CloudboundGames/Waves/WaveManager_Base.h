// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWavesComplete);

UCLASS()
class CLOUDBOUNDGAMES_API AWaveManager_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWaveManager_Base();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWavesComplete OnGameWon;
};
