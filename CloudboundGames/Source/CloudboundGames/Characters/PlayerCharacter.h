// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CloudboundGames/Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

class UHealthComponent;
struct FEnhancedInputActionValueBinding;

UCLASS(Blueprintable, Abstract)
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Input handlers for movement. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHorizontalMovementTriggered();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnVerticalMovementTriggered();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRollTriggered();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RollPlayer();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetRollCooldown();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetLaunchVelocity() const;

	FEnhancedInputActionValueBinding* MoveHorizontalActionBinding;
	FEnhancedInputActionValueBinding* MoveVerticalActionBinding;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Roll properties */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	bool bCanRoll = true;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	float RollCooldownTime = 2.0f;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category=Roll, meta=(AllowPrivateAccess = "true"))
	float RollSpeed;
};

