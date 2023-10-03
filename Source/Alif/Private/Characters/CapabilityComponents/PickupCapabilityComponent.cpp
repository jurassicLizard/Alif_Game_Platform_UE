// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"
#include "AlifLogging.h"
#include "Interfaces/PickupCapabilityInterface.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Items/Weapons/BaseWeapon.h"


// Sets default values for this component's properties
UPickupCapabilityComponent::UPickupCapabilityComponent():
	PickupCmdState(EPickupCmdState::NONE),
	PendingItemToPickUp(nullptr),
	bIsValidComponentUse(false),
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

	bIsValidComponentUse = ValidateUseableState();
	// ...
	
}


// Called every frame
void UPickupCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsValidComponentUse)
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Tick is unusable  and will be disabled. it is useless due to unsatisfied must haves in %s"),*GetReadableName(),*GetName());
		SetComponentTickEnabled(false);

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
					if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
					{
						if(!OwnerIface->IsMoving())
						{
							if(PendingItemToPickUp)
							{
								UE_LOG(LogAlifDebug, Warning, TEXT("%s : %s  has stopped with PENDING Pickup State . attempting to pick up %s"),*GetReadableName(),*GetOwner()->GetName(),*PendingItemToPickUp->GetName());
								// OwnerIface->PickUpItem(PendingItemToPickUp); //WARNING dont call pickupitem here it is called by the pickup interface. this can lead to recursions and or unintended consequences
								if(ABaseCharacter* OwnerChar = Cast<ABaseCharacter>(GetOwner())) //FIXME this should be changed from BaseCharacter to Interface FUnction
								{
									//we already checked for inventory null pointer when we did validity checks
									if(ABaseWeapon* WeaponToPickup = Cast<ABaseWeapon>(PendingItemToPickUp))
									{
											OwnerChar->GetInventoryCapabilityComponent()->AddMainWeaponToInventory(WeaponToPickup);


									}//handle other items in else

								}else
								{
									UE_LOG(LogAlifDebug, Error, TEXT("%s : we are in the pickup loop yet our item is unpickable , this is terrible since we conducted checks"),*GetReadableName());
									ResetPickupCommand();
									break;
								}
								CompletePickupCommand();
							}else
							{
								UE_LOG(LogAlifDebug, Error, TEXT("%s : %s weird , we queued a pickup command but passed a nullptr as object to pickup"),*GetReadableName(),*GetOwner()->GetName());
								ResetPickupCommand();
							}

						}else
						{
							UE_LOG(LogAlifDebug, Warning, TEXT("%s : Character has PENDING Pickup state and is moving waiting till he stops"),*GetOwner()->GetName());
						}
					}
					//TODO add unreal delegates here (11.07.2023 : do we have to ? it appears overkill for now)


					

					break;
				}
				case EPickupCmdState::CANCELLING :
				{
					//we just completePickup and drop pending pickup command
					ResetPickupCommand();
					break;
				}
				case EPickupCmdState::FINALIZING :
				{
					ResetPickupCommand();
					break;
				}

				default:
				{
					UE_LOG(LogAlifDebug, Error, TEXT("%s : We are in an unidentified state . this is fatal"),*GetReadableName());
					break;
				}

			}

	}


}


void UPickupCapabilityComponent::QueuePickupCommand(const ABaseItem* PendingItemToPickUpNew)
{
	PickupCmdState = EPickupCmdState::PENDING;
	UE_LOG(LogAlifDebug, Warning, TEXT("%s : Queing pickup command"),*GetReadableName());
	PendingItemToPickUp = const_cast<ABaseItem*>(PendingItemToPickUpNew);

}

void UPickupCapabilityComponent::CancelPickupCommand()
{
	PickupCmdState = EPickupCmdState::CANCELLING;
	UE_LOG(LogAlifDebug, Warning, TEXT("%s : Cancelling pickup command"),*GetReadableName());

}


void UPickupCapabilityComponent::CompletePickupCommand()
{
	PickupCmdState = EPickupCmdState::FINALIZING;
	UE_LOG(LogAlifDebug, Warning, TEXT("%s : finishing pickup command"),*GetReadableName());

}

void UPickupCapabilityComponent::ResetPickupCommand()
{
	PickupCmdState = EPickupCmdState::NONE;
	PendingItemToPickUp = nullptr;
	UE_LOG(LogAlifDebug, Warning, TEXT("%s : resetting pickup command"),*GetReadableName());

}

// bool UPickupCapabilityComponent::PickUpWeapon(ABaseWeapon* BaseWeaponOut) const
// {
// 	//general algo
// 	//Pickup weapon should be triggered from squad character or upon cursor click
// 	//conduct sweep and check if weapon hat floating pickable class
// 	//(optional)weapon should implement onpickedup and ondropped interface if possible
// 	//if it has the floating pickable component we continue. else we break
// 	//Check if owner inventory is full
// 		//if yes , main weapon replaces current weapon, current weapon is dropped
// 		//if no picked up weapon is main weapon and inventory is pushed back from first slot
	
// 	//weapon pickup procedure with empty inventory
// 	//Hide Currently Deployed weapon and disable its collision if it has one
// 	//disable pickable item components floating if it has it and attach it to socket
// 	//set it as MainWeapon and skid inventory back

// 	return false;
// }


bool UPickupCapabilityComponent::ValidateUseableState()
{
	if(!GetOwner())
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Has No valid Owner , weird how this loaded"),*GetReadableName());
		return false;
	}else if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
	{
		return true;

	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Owner %s must implement UPickupCapabilityInterface"),*GetReadableName(),*GetOwner()->GetName());
		return false;
	}

	
}


