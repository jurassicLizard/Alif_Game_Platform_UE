// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "SelectAction.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API USelectAction : public UInputAction
{
	GENERATED_BODY()
	
	
public:

	USelectAction();

private:

	UPROPERTY()
	TObjectPtr<UInputTrigger> PressedTrigger;



	
};
