// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemComponents/FloatingPickableComponent.h"
#include "AlifLogging.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Items/BaseItem.h"

// Sets default values for this component's properties
UFloatingPickableComponent::UFloatingPickableComponent():
	Amplitude(0.5f),
	TimeConstant(5.f),
	RotationSpeed(90.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if(GetOwner() && GetDesiredParentAttachmentPoint())
	{
		PickableCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Pickable Item Capsule Comp");
		UE_LOG(LogAlifDebug, Warning, TEXT("%s Capsule Component is not attached as root . this may cause problems when using native unreal functions like move to location. use this at your own discretion"),*GetReadableName());
		/**Begin Conduct Capsule transforms*/
		AddCapsuleWorldLocationOffset();
		AddCapsuleWorldRotationOffset();
		SetPickableCapsuleHalfHeight();
		SetPickableCapsuleRadius();
		/**End Conduct Capsule transforms*/
		PickableCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PickableCapsuleComp->SetGenerateOverlapEvents(true);
		PickableCapsuleComp->SetupAttachment(GetDesiredParentAttachmentPoint());

	}else
	{
		UE_LOG(LogAlifDebug, Warning, TEXT("%s : The Owning Actor Doesnot Exist or This is the default class or we are attaching this component to a nullptr"),*GetReadableName());
	}



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
		if(!GetOwner()->GetAttachParentActor())
		{
			SetPickedState(EPickedState::DROPPED);

		}else
		{
			SetPickedState(EPickedState::PICKED);

		}

		if(GetPickedState() == EPickedState::DROPPED)
		{
			HandleDroppedState(DeltaTime);
		}


	}else
	{
		UE_LOG(LogAlifDebug, Warning, TEXT("%s reports no owner attached to it and can therefore not conduct its tasks"),*GetName());

	}

	// ...
}

void UFloatingPickableComponent::SetPickedState(EPickedState const& NewPickedState) 
{ 
	if(NewPickedState != GetPickedState())
	{
		PickedState = NewPickedState;
		FString PickedString = ((GetPickedState() == EPickedState::DROPPED) ? "Dropped" : "Picked");
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Setting picked State for %s to %s"),*GetReadableName(),*GetOwner()->GetName(),*PickedString);

	}

}
void UFloatingPickableComponent::HandleDroppedState(float DeltaTime)
{
		GetOwner()->AddActorWorldOffset(FVector(0.f,0.f,GetTransformedSine()));

		FRotator RotationOffset = FRotator(0.f,(RotationSpeed * DeltaTime),0.f);

		GetOwner()->AddActorWorldRotation(RotationOffset);

}

float UFloatingPickableComponent::GetTransformedSine()
{
	return (Amplitude * UKismetMathLibrary::Sin(TimeConstant * UGameplayStatics::GetTimeSeconds(this)));
}

USceneComponent* UFloatingPickableComponent::GetDesiredParentAttachmentPoint()
{
	if(ABaseItem* ParentItem = Cast<ABaseItem>(GetOwner()))
	{
		return ParentItem->GetChildrenAttachmentComp();
	}

	return nullptr;
}



void UFloatingPickableComponent::AddCapsuleWorldRotationOffset(FRotator WorldRotationOffset)
{
	if(PickableCapsuleComp)
	{
		PickableCapsuleComp->AddWorldRotation(WorldRotationOffset);
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to add offset on a non existing capsule. Aborting"),*GetReadableName());
	}
}

void UFloatingPickableComponent::AddCapsuleWorldLocationOffset(FVector WorldLocationOffset)
{
	if(PickableCapsuleComp)
	{
		PickableCapsuleComp->AddWorldOffset(WorldLocationOffset);
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to add offset on a non existing capsule. Aborting"),*GetReadableName());
	}

}


void UFloatingPickableComponent::SetPickableCapsuleHalfHeight(float HalfHeight/**default value in header*/)
{
	if(PickableCapsuleComp)
	{
		PickableCapsuleComp->SetCapsuleHalfHeight(HalfHeight);
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to modify a non existing capsule. Aborting"),*GetReadableName());
	}
}


void UFloatingPickableComponent::SetPickableCapsuleRadius(float Radius/**default value in header*/)
{
		if(PickableCapsuleComp)
	{
		PickableCapsuleComp->SetCapsuleRadius(Radius);
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to modify a non existing capsule. Aborting"),*GetReadableName());
	}

}
