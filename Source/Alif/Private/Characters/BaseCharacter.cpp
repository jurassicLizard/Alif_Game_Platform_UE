// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AlifLogging.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"
#include "Characters/BaseCharMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer): 
	Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharMovementComponent>(Super::CharacterMovementComponentName)),// We override the default movement component in order to set some protected values
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
	if(GetCharacterMovement())
	{
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->bIgnoreBaseRotation = true;
			GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;			

	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : unable to get character mesh component this is fatal"),*GetName());
	}

	


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



