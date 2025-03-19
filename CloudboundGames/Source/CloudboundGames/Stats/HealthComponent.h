// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, class UHealthComponent*, Actor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase=true))
class CLOUDBOUNDGAMES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintCallable)
	FOnDeath OnKilled;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
