// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "UObject/Interface.h"
#include "InventoryCapabilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInventoryCapabilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ALIF_API IInventoryCapabilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual uint8 GetMaxWeapons() = 0;
	virtual bool TriggerWeaponSwitch() = 0;

	friend UInventoryCapabilityComponent;
};
