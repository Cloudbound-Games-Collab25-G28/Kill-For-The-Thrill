// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSelect_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSelected, enum EWeaponType, Weapon);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CLOUDBOUNDGAMES_API UWeaponSelect_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeaponSelected SelectWeapon;
};
