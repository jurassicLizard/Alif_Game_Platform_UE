// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Interfaces/PickupCapabilityInterface.h"
#include "AlifLogging.h"
#include "Interfaces/InventoryCapabilityInterface.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UInventoryCapabilityComponent::UInventoryCapabilityComponent():
	ItemPendingStowAwayAction(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UInventoryCapabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//WARNING currenty we are setting tick to disabled
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryCapabilityComponent::AddWeaponToInventoryAtIdx(ABaseWeapon const* NewBaseWeapon, int32 Idx)
{
	//this is a helper function used internally. DO NOT expose this publicly
	if(!NewBaseWeapon)
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to Add a Null Weapon or non ABaseWeapon Item . this is fatal"),*GetReadableName());
		return false;
	}
	const bool bIsDuplicate = HasWeaponOfSameTypeInInventory(const_cast<ABaseWeapon*>(NewBaseWeapon)); 
	
	if(!HasRemainingInventoryCapacity())
	{

			if(GetLastWeapon()/**FIXME and LastWeapon is Droppable*/)
			{
				UE_LOG(LogAlifDebug, Warning, TEXT("%s : Queuing Drop Action for %s"),*GetReadableName(),*GetLastWeapon()->GetName());
				ItemPendingDropAction = GetLastWeapon();
			}


		// if(!RemoveWeaponFromInvAndDestroy(GetMainWeapon())) //FIXME change this to dropordestroy function depending on state of weapon
		// {
		// 	UE_LOG(LogAlifDebug, Error, TEXT("%s : Was unable to remove Main weapon from inventory . this is unexpected, skipping AddMainWeapon operation"),*GetReadableName());
		// 	return false;
		// }

	}
	
		
	if(!bIsDuplicate)
	{
		if(GetMainWeapon() && IsMainWeaponIdx(Idx))
		{
			//if this is a main weapon idx we check for mainweapon existence and hide/drop it if it is there
			UE_LOG(LogAlifDebug, Warning, TEXT("%s : Queuing Stow away Action for %s"),*GetReadableName(),*GetLastWeapon()->GetName());
			ItemPendingStowAwayAction = GetMainWeapon();
		}

		if(ItemPendingStowAwayAction)
		{
			if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
			{				
				UE_LOG(LogAlifDebug, Warning, TEXT("%s : Delegating Stowing of %s to %s through Stow Item interface"),*GetReadableName(),*NewBaseWeapon->GetName(),*GetOwner()->GetName());
				OwnerIface->OnStowItem(ItemPendingStowAwayAction);
				ItemPendingStowAwayAction = nullptr;
			}
		}

		if(ItemPendingDropAction)
		{
			if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
			{				
				
				if(RemoveWeaponFromInventory(Cast<ABaseWeapon>(ItemPendingDropAction)))
				{
					UE_LOG(LogAlifDebug, Warning, TEXT("%s : Delegating Dropping of %s to %s through Drop Item interface"),*GetReadableName(),*NewBaseWeapon->GetName(),*GetOwner()->GetName());
					OwnerIface->OnDropItem(ItemPendingDropAction);
					ItemPendingDropAction = nullptr;

				} //we need to pack this line and the next in a utility FUnction to avoid making mistakes

			}

		}
		//FIX ME CONDUCT A SECOND INVENTORY CHECK HERE
		WeaponsInventoryArray.Insert(const_cast<ABaseWeapon*>(NewBaseWeapon),Idx);
		if (GEngine)
		{
			
			for(int i = 0; i< GetWeaponInventorySize() ; i++)
			{
				FString MsgString = (GetWeaponAt(i) ? GetWeaponAt(i)->GetName() : "None");
				GEngine->AddOnScreenDebugMessage((4 + i),10,FColor::Red,FString::Printf(TEXT("Weapon at %d : %s"),i,*MsgString));

			}
		}

		return true;

	}else
	{
		UE_LOG(LogAlifDebug, Warning, TEXT("%s : Found Duplicate Item for %s . resetting and aborting"),*GetReadableName(),*NewBaseWeapon->GetName());
		ResetAllPendingItemActions(); //we reset pending actions since we are not adding anything
	}

	


	ResetAllPendingItemActions(); //we reset all pending actions in case something slipped due to unknown error
    return false;
}

bool UInventoryCapabilityComponent::AddMainWeaponToInventory(ABaseWeapon const* NewBaseWeapon) 
{
	if(!NewBaseWeapon)
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to pick an  null pointer. aborting.  there is something wrong with the api this shouldnot happen."),*GetReadableName());
		return false;
	}

	if(!NewBaseWeapon->HasPickableCapability()) //TODO Add EquipabaleCapability or make pickablecapability handle isEquipable and iSdroppable
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to pick an item with no pickable capability . aborting.  there is something wrong with the api this shouldnot happen."),*GetReadableName());
		return false;
	}


	if(AddWeaponToInventoryAtIdx(NewBaseWeapon,0))
	{
		if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
		{	
			//AddWeaponToInventoryAtIDx already checks if the weapon is inserted as a main weapon and handles Hiding it
			UE_LOG(LogAlifDebug, Warning, TEXT("%s : Delegating Pickup of %s to %s through Pickup interface"),*GetReadableName(),*NewBaseWeapon->GetName(),*GetOwner()->GetName());
			OwnerIface->OnPickUpItem(NewBaseWeapon);
			
			return true;

		}
	}

	return false;

}


bool UInventoryCapabilityComponent::RemoveWeaponFromInvAndDestroy(ABaseWeapon* DeletedBaseWeapon)
{
	if(DeletedBaseWeapon)
	{
		 UE_LOG(LogAlifDebug, Warning, TEXT("%s : Attempting to Destroy %s"),*GetReadableName(),*DeletedBaseWeapon->GetName());
		 return RemoveWeaponFromInventory(DeletedBaseWeapon) && DeletedBaseWeapon->Destroy();	 


	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to remove nullptr this is not good"),*GetReadableName());
	}

	return false;
	
}





ABaseWeapon* UInventoryCapabilityComponent::GetWeaponAt(int32 Idx) const
{
	if(WeaponsInventoryArray.IsValidIndex(Idx) && WeaponsInventoryArray[Idx])
	{
		UE_LOG(LogAlifDebug, Warning, TEXT("%s : Attempting to retrieve Weapon with Name %s"),*GetReadableName(),*WeaponsInventoryArray[Idx]->GetName());
		return WeaponsInventoryArray[Idx];
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to access Weapon inventory at %d but nothing here"),*GetReadableName(),Idx);
		return nullptr;
	}

}


void UInventoryCapabilityComponent::ResetAllPendingItemActions()
{
	ItemPendingDropAction = nullptr;
	ItemPendingStowAwayAction = nullptr;
}


bool UInventoryCapabilityComponent::HasWeaponOfSameTypeInInventory(ABaseWeapon* WeaponToCheck) const
{
	if(!WeaponToCheck)
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Passing a null pointer to check its existance . this is not good . check api"),*GetReadableName());
		return false;
	}
	for(const ABaseWeapon* CurWeapon : WeaponsInventoryArray)
	{
		if(!CurWeapon)
		{
			UE_LOG(LogAlifDebug, Error, TEXT("%s : Checking against Nullpointer in inventory .Meaning inventory has not been properly sanitized. this is not good . check api"),*GetReadableName());
			return false;
		}

		//retrieve the Class Default Object for both comparabales to check if they are of the same type . THank you KISMET xD
		UObject* WeaponToCheckCDO = WeaponToCheck->GetClass()->GetDefaultObject(false);
		UObject* WeaponToCompareCDO = CurWeapon->GetClass()->GetDefaultObject(false);

		if(UKismetMathLibrary::EqualEqual_ObjectObject(WeaponToCheckCDO,WeaponToCompareCDO))
		{
			UE_LOG(LogAlifDebug, Display, TEXT("%s : Found Objects of same type %s and %s"),*GetReadableName(),*WeaponToCheck->GetName(),*CurWeapon->GetName());
			return true;
		}
	}

	return false;

}

ABaseWeapon* UInventoryCapabilityComponent::CycleWeaponsInInventory()
{
	

	if(GetWeaponInventorySize() > 1)
	{
		if(IPickupCapabilityInterface* OwnerIface = Cast<IPickupCapabilityInterface>(GetOwner()))
		{
			ABaseWeapon* FirstWeapon = GetMainWeapon();
			
			GetActiveWeaponInventory().RemoveSingle(FirstWeapon);
			GetActiveWeaponInventory().Push(FirstWeapon);

			//Call relevant pickup and stow interfaces on actor in order to setup the build of meshes

			OwnerIface->OnStowItem(FirstWeapon);
			OwnerIface->OnPickUpItem(GetMainWeapon());

			return GetMainWeapon();
			
		}


	}

	return nullptr;
}

bool UInventoryCapabilityComponent::SwitchToNextWeapon()
{
	if(CycleWeaponsInInventory())
	{
		// conduct switch of weapon and call interface function of switch which would be implemented by the actor
		
		if(IInventoryCapabilityInterface* OwningActorIface = Cast<IInventoryCapabilityInterface>(GetOwner()))
		{
			OwningActorIface->TriggerWeaponSwitch();
			return true;
			
		}
		else
		{
			UE_LOG(LogAlifDebug,Error,TEXT("Incapable of switching weapon , something really terrible happened , %s has no owner"),*GetName());
		}
	}
	


	return false;
}

uint8 UInventoryCapabilityComponent::GetMaxWeaponInventorySize() const
{
	if(IInventoryCapabilityInterface* OwningActorIface = Cast<IInventoryCapabilityInterface>(GetOwner()) )
	{
		return OwningActorIface->GetMaxWeapons();
	}

	UE_LOG(LogAlifDebug,Error,TEXT("Was Unable to find Owner for the component : %s : This is fatal"),*GetName());
	return 0;
}
bool UInventoryCapabilityComponent::HasRemainingInventoryCapacity() const {return (WeaponsInventoryArray.Num() < GetMaxWeaponInventorySize());}

