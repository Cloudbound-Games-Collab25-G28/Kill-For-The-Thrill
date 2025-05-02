// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKilled, class UHealthComponent*, HealthComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, UHealthComponent*, HealthComponent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase=true))
class CLOUDBOUNDGAMES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnKilled OnKilled;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintReadWrite)
	float Health = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetMaxHealth(float NewHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetInvincibility(bool newValue);

protected:
	UPROPERTY(BlueprintReadOnly, Category=Health, meta=(AllowPrivateAccess=true))
	bool isInvincible = false;
	
	// Called when the game starts
	virtual void BeginPlay() override;
};
