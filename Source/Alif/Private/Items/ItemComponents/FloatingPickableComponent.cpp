// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemComponents/FloatingPickableComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFloatingPickableComponent::UFloatingPickableComponent():
	Amplitude(0.5f),
	TimeConstant(5.f),
	RotationSpeed(90.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingPickableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFloatingPickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetOwner())
	{
		GetOwner()->AddActorWorldOffset(FVector(0.f,0.f,GetTransformedSine()));

		FRotator RotationOffset = FRotator(0.f,(RotationSpeed * DeltaTime),0.f);

		GetOwner()->AddActorWorldRotation(RotationOffset);

	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s reports no owner attached to it and can therefore not conduct its tasks"),*GetName());

	}

	// ...
}


float UFloatingPickableComponent::GetTransformedSine()
{
	return (Amplitude * UKismetMathLibrary::Sin(TimeConstant * UGameplayStatics::GetTimeSeconds(this)));
}

