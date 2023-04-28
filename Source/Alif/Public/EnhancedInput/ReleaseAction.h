// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "ReleaseAction.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API UReleaseAction : public UInputAction
{
	GENERATED_BODY()
	
	
public:

	UReleaseAction();

private:

	UPROPERTY()
	TObjectPtr<UInputTrigger> PressedTrigger;
	
};
