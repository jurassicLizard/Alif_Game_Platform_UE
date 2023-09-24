// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/InventoryCapabilityInterface.h"
#include "Interfaces/SelectableActorInterface.h"
#include "Interfaces/PickupCapabilityInterface.h"

#include "MainSquadCharacter.generated.h"


/**
 * 
 */
class ABaseItem;

UCLASS()
class ALIF_API AMainSquadCharacter : public ABaseCharacter, public ISelectableActorInterface, public IPickupCapabilityInterface, public IInventoryCapabilityInterface
{
	GENERATED_BODY()

/**Class Interface*/
public:

	AMainSquadCharacter(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void Tick(float DeltaTime) override;
	void BeginPlay() override;


/**End Class Interface*/



private:

	FName WeaponMainSocketName;
	FName BackpackSocketName;
/**Implemented Interface*/

protected:
	virtual void OnSelectionGained() override;
	virtual void OnPrimaryActionTrigger(FVector NewLocation) override;
	virtual void OnSecondaryActionTrigger(FVector NewLocation) override;
	UFUNCTION()
	virtual void OnTriggeredPickupCmd(const ABaseItem* PickedUpActorCandidate) override;
	virtual void OnCancelledPickupCmd() override;
	virtual bool CanQueryMoveState() override;
	virtual bool IsMoving() override;
	UFUNCTION()
	virtual void OnPickUpItem(const ABaseItem* ItemToPickUp) override;
	UFUNCTION()
	virtual void OnDropItem(const ABaseItem* ItemToDrop) override;
	UFUNCTION()
	virtual void OnStowItem(const ABaseItem* ItemToStow) override;
	UFUNCTION()
	virtual void SwitchToNextWeapon() override;
	//FIXME add initiate Pickup item , initiate stow item maybe ??

public:
	virtual uint8 GetMaxWeapons() override { return 2;}



/**End Implemented Interface*/






	
};
