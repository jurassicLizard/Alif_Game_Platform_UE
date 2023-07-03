// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"


// Sets default values for this component's properties
UInventoryCapabilityComponent::UInventoryCapabilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	WeaponsInventoryArray.SetNum(MaxWeapons);

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

bool UInventoryCapabilityComponent::AddWeaponToInventoryAtIdx(ABaseWeapon *NewBaseWeapon, int32 Idx)
{
	bool IsDuplicate = WeaponsInventoryArray.Find(NewBaseWeapon);
	if(!IsDuplicate)
	{
		WeaponsInventoryArray.Insert(NewBaseWeapon,Idx);

	}
    return IsDuplicate;
}
