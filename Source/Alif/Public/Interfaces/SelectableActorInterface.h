// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SelectableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ALIF_API ISelectableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnSelectionGained() = 0;
	virtual void OnPrimaryActionTrigger(FVector NewLocation) = 0;
	virtual void OnSecondaryActionTrigger(FVector NewLocation) = 0;
	
	
};
