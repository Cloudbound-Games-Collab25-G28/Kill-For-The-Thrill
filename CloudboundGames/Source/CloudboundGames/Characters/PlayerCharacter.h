// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CloudboundGames/Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

struct FEnhancedInputActionValueBinding;

UCLASS(Blueprintable, Abstract)
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void PostInitializeComponents() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Input handlers for movement. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHorizontalMovementTriggered();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnVerticalMovementTriggered();

	FEnhancedInputActionValueBinding* MoveHorizontalActionBinding;
	FEnhancedInputActionValueBinding* MoveVerticalActionBinding;

	/** Roll component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UDodgeRollComponent* DodgeRollComponent;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

