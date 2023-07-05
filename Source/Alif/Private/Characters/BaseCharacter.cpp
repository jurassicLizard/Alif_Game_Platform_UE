// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter():
	InventoryCapabilityComp(nullptr),
	PickupCapabilityComp(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	//set standard pawn settings

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false; //strategy top down game

	//Set MovementSettings
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



