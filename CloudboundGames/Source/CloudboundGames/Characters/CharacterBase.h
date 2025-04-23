// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract, Blueprintable)
class CLOUDBOUNDGAMES_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACharacterBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void SetupAudioEvents();
};
