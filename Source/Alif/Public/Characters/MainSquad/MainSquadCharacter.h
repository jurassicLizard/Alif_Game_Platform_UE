// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/SelectableActorInterface.h"
#include "MainSquadCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API AMainSquadCharacter : public ABaseCharacter, public ISelectableActorInterface
{
	GENERATED_BODY()

/**Class Interface*/
public:

	AMainSquadCharacter();
	void BeginPlay() override;

protected:
	void OnSelectionGained() override;
	void OnPrimaryActionTrigger(FVector NewLocation) override;
	void Tick(float DeltaTime) override;

/**End Class Interface*/


private:

UPROPERTY()
TWeakObjectPtr<class APrototypeRifle> MainWeaponObj;
	
	
};
