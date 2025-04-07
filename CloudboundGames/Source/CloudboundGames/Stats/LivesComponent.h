// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LivesComponent.generated.h"

class UHealthComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeLost, class ULivesComponent*, LivesComponent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CLOUDBOUNDGAMES_API ULivesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULivesComponent();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int MaxLives = 3;

	UPROPERTY(BlueprintReadWrite)
	int CurrentLives = 3;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnLifeLost OnAllLivesLost;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnLifeLost OnLifeLost;

	void SetupComponent(UHealthComponent* HealthComponent);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RevivePlayer(UHealthComponent* HealthComponent);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnKilled(UHealthComponent* HealthComponent);
};
