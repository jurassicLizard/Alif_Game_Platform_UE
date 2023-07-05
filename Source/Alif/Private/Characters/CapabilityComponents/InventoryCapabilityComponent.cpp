// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Items/Weapons/BaseWeapon.h"

// Sets default values for this component's properties
UInventoryCapabilityComponent::UInventoryCapabilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	// ...
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
	if(!NewBaseWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Attempting to Add a Null Weapon . this is fatal"),*GetReadableName());
		return false;
	}

	bool IsDuplicate = (WeaponsInventoryArray.Find(const_cast<ABaseWeapon*>(NewBaseWeapon)) > 0);

	if(!IsDuplicate)
	{
		WeaponsInventoryArray.Insert(const_cast<ABaseWeapon*>(NewBaseWeapon),Idx);

	}
    return !IsDuplicate;
}


ABaseWeapon* UInventoryCapabilityComponent::GetWeaponAt(int32 Idx) const
{
	if(WeaponsInventoryArray.IsValidIndex(Idx) && WeaponsInventoryArray[Idx])
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Attempting to return Weapon with Name %s"),*GetReadableName(),*WeaponsInventoryArray[Idx]->GetName());
		return WeaponsInventoryArray[Idx];
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Attempting to access Weapon inventory at %d but nothing here"),*GetReadableName(),Idx);
		return nullptr;
	}

}