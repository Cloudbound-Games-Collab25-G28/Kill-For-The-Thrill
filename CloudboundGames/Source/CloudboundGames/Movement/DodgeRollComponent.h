// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeRollComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRollEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class CLOUDBOUNDGAMES_API UDodgeRollComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDodgeRollComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRollTriggered();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RollPlayer();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetRollCooldown();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDashFinished();

	UPROPERTY(BlueprintAssignable)
	FOnRollEvent OnRollStarted;
	UPROPERTY(BlueprintAssignable)
	FOnRollEvent OnRollRecovered;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta=(AllowPrivateAccess = "true"))
    FVector GetLaunchVelocity() const;

	TObjectPtr<class ACharacter> Character;
	TObjectPtr<class UHealthComponent> HealthComp;

private:
	/** Roll properties */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	bool bCanRoll = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	float RollCooldownTime = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	float InvincibilityDuration = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	float RollSpeed;
};
