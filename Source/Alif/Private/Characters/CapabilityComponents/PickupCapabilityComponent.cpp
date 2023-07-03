// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"


// Sets default values for this component's properties
UPickupCapabilityComponent::UPickupCapabilityComponent():
	DefaultWeaponSocket("WeaponRSocket")
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
	//WARNING Tick is currently disabled
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

