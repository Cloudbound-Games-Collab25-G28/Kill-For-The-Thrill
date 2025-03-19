// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "TP_TopDownPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATP_TopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATP_TopDownPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Horizontal Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* HorizontalMovementAction;
	/** Vertical Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* VerticalMovementAction;
	/** Roll Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RollAction;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerKilled(class UHealthComponent* healthComponent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=HUD, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=HUD, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameOverWidgetType;

	TObjectPtr<UUserWidget> HUDWidget;
	TObjectPtr<UUserWidget> GameOverWidget;
	
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void OnPossess(APawn* InPawn);

private:
	
};


