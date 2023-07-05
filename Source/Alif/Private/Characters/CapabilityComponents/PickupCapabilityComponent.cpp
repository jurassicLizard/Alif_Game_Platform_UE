// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"
#include "Interfaces/PickupCapabilityInterface.h"
#include "Items/Weapons/BaseWeapon.h"


// Sets default values for this component's properties
UPickupCapabilityComponent::UPickupCapabilityComponent():
	PickupCmdState(EPickupCmdState::NONE),
	PendingItemToPickUp(nullptr),
	DefaultWeaponSocket("WeaponRSocket")

{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;




	// ...
}


// Called when the game starts
void UPickupCapabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPickupCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!ValidateUseableState())
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Tick is unusable for PickupComponent it is useless due to unsatisfied must haves in %s"),*GetReadableName(),*GetName());

		return;
			
	}else
	{
			//TODO handle Pickup Weapon when state allows it
			switch(GetPickupCmdState())
			{
				case EPickupCmdState::NONE :
				{
					break;
				}
				case EPickupCmdState::PENDING :
				{
					//check if is Moving then we skip else we conduct pickup procedure and transition to completed


					break;
				}
				case EPickupCmdState::CANCELLING :
				{
					//we just completePickup and drop pending pickup command
					CompletePickupCommand();
					break;
				}
				case EPickupCmdState::COMPLETED :
				{
					break;
				}

				default:
				{
					UE_LOG(LogTemp, Error, TEXT("%s : We are in an unidentified state . this is fatal"),*GetReadableName());
					break;
				}

			}

	}


}


void UPickupCapabilityComponent::QueuePickupCommand(const ABaseItem* PendingItemToPickUpNew)
{
	PickupCmdState = EPickupCmdState::PENDING;
	PendingItemToPickUp = const_cast<ABaseItem*>(PendingItemToPickUpNew);

}

void UPickupCapabilityComponent::CancelPickupCommand()
{
	PickupCmdState = EPickupCmdState::CANCELLING;
}


void UPickupCapabilityComponent::CompletePickupCommand()
{
	PickupCmdState = EPickupCmdState::COMPLETED;
	PendingItemToPickUp = nullptr;
	SetPickupCmdState(EPickupCmdState::NONE);
}

bool UPickupCapabilityComponent::PickUpWeapon(ABaseWeapon* BaseWeaponOut) const
{
	//general algo
	//Pickup weapon should be triggered from squad character or upon cursor click
	//conduct sweep and check if weapon hat floating pickable class
	//(optional)weapon should implement onpickedup and ondropped interface if possible
	//if it has the floating pickable component we continue. else we break
	//Check if owner inventory is full
		//if yes , main weapon replaces current weapon, current weapon is dropped
		//if no picked up weapon is main weapon and inventory is pushed back from first slot
	
	//weapon pickup procedure with empty inventory
	//Hide Currently Deployed weapon and disable its collision if it has one
	//disable pickable item components floating if it has it and attach it to socket
	//set it as MainWeapon and skid inventory back

	return false;
}


bool UPickupCapabilityComponent::ValidateUseableState()
{
	if(!GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Has No valid Owner , weird how this loaded"),*GetReadableName());
		return false;
	}else if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
	{
		return true;

	}else
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Owner %s must implement UPickupCapabilityInterface"),*GetReadableName(),*GetOwner()->GetName());
		return false;
	}

	
}


