// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/SelectableActorInterface.h"
#include "Interfaces/PickupCapabilityInterface.h"

#include "MainSquadCharacter.generated.h"


/**
 * 
 */
class ABaseItem;

UCLASS()
class ALIF_API AMainSquadCharacter : public ABaseCharacter, public ISelectableActorInterface, public IPickupCapabilityInterface
{
	GENERATED_BODY()

/**Class Interface*/
public:

	AMainSquadCharacter(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void Tick(float DeltaTime) override;
	void BeginPlay() override;


/**End Class Interface*/


/**Implemented Interface*/

protected:
	virtual void OnSelectionGained() override;
	virtual void OnPrimaryActionTrigger(FVector NewLocation) override;
	virtual void OnSecondaryActionTrigger(FVector NewLocation) override;
	virtual void OnTriggeredPickupCmd(const ABaseItem* PickedUpActorCandidate) override;
	virtual void OnCancelledPickupCmd() override;
	virtual bool CanQueryMoveState() override;
	virtual bool IsMoving() override;


/**End Implemented Interface*/






	
};
