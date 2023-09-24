// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "SwitchWeaponAction.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API USwitchWeaponAction : public UInputAction
{
	GENERATED_BODY()
public:
	USwitchWeaponAction();
	
private:
	UPROPERTY()
	TObjectPtr<UInputTrigger> PressedTrigger;
	
	
};
