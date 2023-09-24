// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "PickupCapabilityInterface.generated.h"

class ABaseItem;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupCapabilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class ALIF_API IPickupCapabilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnTriggeredPickupCmd(const ABaseItem* PickedUpActorCandidate) = 0;
	virtual void OnCancelledPickupCmd() = 0;

	virtual bool CanQueryMoveState() {return false;}
	virtual bool IsMoving() = 0;

	virtual void OnPickUpItem(const ABaseItem* ItemToPickUp) = 0;
	virtual void OnDropItem(const ABaseItem* ItemToDrop) = 0;
	virtual void OnStowItem(const ABaseItem* ItemToStow) = 0;
	
	
};
