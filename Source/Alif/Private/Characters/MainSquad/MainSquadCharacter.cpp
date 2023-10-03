// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainSquad/MainSquadCharacter.h"
#include "AlifLogging.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Items/Weapons/Rifles/PrototypeRifle.h"
#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"




AMainSquadCharacter::AMainSquadCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	WeaponMainSocketName(TEXT("WeaponRSocket")),
	BackpackSocketName(TEXT("BackpackWeaponSocket"))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
    //set primary capsule collision component settings
	if(GetCapsuleComponent())
	{
		//Set base Capsule dimensions
			GetCapsuleComponent()->SetCapsuleHalfHeight(93.f);
			GetCapsuleComponent()->SetCapsuleRadius(30.78f);
		//Set base collision settings
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			GetCapsuleComponent()->SetGenerateOverlapEvents(false);
			GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block); //TODO create our own collision preset so that we dont have to manually modify instances

	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Getting a null pointer instead of our capsule component, something really terrible is happening here"),*GetName());
	}


	//Set the location and rotation of the Character Mesh Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -94.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	//Begin Actor components section

	InventoryCapabilityComp = CreateDefaultSubobject<UInventoryCapabilityComponent>(TEXT("Inventory Component"));

	AddOwnedComponent(InventoryCapabilityComp);

	PickupCapabilityComp = CreateDefaultSubobject<UPickupCapabilityComponent>(TEXT("Pickup Capability Component"));

	AddOwnedComponent(PickupCapabilityComp);
	
	//End Actor components section



}

void AMainSquadCharacter::BeginPlay()
{
	Super::BeginPlay();
	//temporary code specific to wraith character
	if(!IsActorTickEnabled()) 
	{
		UE_LOG(LogAlifDebug, Warning, TEXT("%s : is NOT alive and ticking "),*GetName());
	}

	if(USkeletalMeshComponent* CharMesh = GetMesh())
	{
		if(!GetWorld()) 
		{
			UE_LOG(LogAlifDebug, Error, TEXT("Something terrible has happend the world hasnot be created yet : %s"),*GetName());
			return;
		}

		//Hide existing weapon we dont want
		CharMesh->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);



		if(HasInventoryCapability())
		{
					UE_LOG(LogAlifDebug, Warning, TEXT("Has Inventory Attempting to populate Initial Inventory for : %s"),*GetName());

					if(!GetInventoryCapabilityComponent()->AddMainWeaponToInventory(GetWorld()->SpawnActor<APrototypeRifle>(APrototypeRifle::StaticClass())))
					{
						UE_LOG(LogAlifDebug, Error, TEXT("%s : Failed to Add Main Weapon"),*GetName());
					}


		}else
		{
			UE_LOG(LogAlifDebug, Warning, TEXT("%s : Has no Inventory"),*GetName());
		}

		
		

	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("We have a null pointer mesh at %s"),*GetName());
	}
	//end temporary code
}

void AMainSquadCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	FVector TestVector(3.f,3.f,3.f);
	FVector Acceleration = MoveComp->GetCurrentAcceleration();
	FVector Velocity = MoveComp->GetLastUpdateVelocity();


	if(MoveComp)
	{
		if(MoveComp->GetCurrentAcceleration().Size()>0.f)
		{
		 	GEngine->AddOnScreenDebugMessage(1,DeltaTime, FColor::Blue, FString::Printf(TEXT("Acceleration Value : %f"), MoveComp->GetCurrentAcceleration().Size()));

		}


		GEngine->AddOnScreenDebugMessage(2,DeltaTime, FColor::Blue, FString::Printf(TEXT("Velocity Value : %f"), Velocity.Size()));

		 GEngine->AddOnScreenDebugMessage(3,DeltaTime, FColor::Blue, FString::Printf(TEXT("TestVector Value : %f"), TestVector.Size()));

	}

	
}




//Interface Implementation
void AMainSquadCharacter::OnSelectionGained()
{
	UE_LOG(LogAlifDebug, Warning, TEXT("%s reports being selected"),*GetName());
}

void AMainSquadCharacter::OnPrimaryActionTrigger(FVector NewLocation)
{
	UE_LOG(LogAlifDebug, Warning, TEXT("%s reports attempting to move"),*GetName());

	//TODO make sure AIController is always Created

	if(AAIController* Controller = Cast<AAIController>(GetController()))
	{
		Controller->MoveToLocation(NewLocation);
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s has no AI Controller and cannot be controlled , this is fatal"),*GetName());
	}


	// AddMovementInput(GetActorForwardVector(),1000.f); //TODO write notes about this not working for unpossessed pawns
	// AddMovementInput((GetActorLocation() - NewLocation));



}

void AMainSquadCharacter::OnSecondaryActionTrigger(FVector NewLocation)
{
	
}


void AMainSquadCharacter::OnTriggeredPickupCmd(const ABaseItem* PickedUpActorCandidate)
{
	if(HasPickupCapability())
	{
		PickupCapabilityComp->QueuePickupCommand(PickedUpActorCandidate);

	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Implementing PickupCapabilityInterface but having no PickupCapabilityCOmponent is not possible . this is FATAL"),*GetName());
	}

}
void AMainSquadCharacter::OnCancelledPickupCmd()
{
	if(HasPickupCapability())
	{
		PickupCapabilityComp->CancelPickupCommand();
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Implementing PickupCapabilityInterface but having no PickupCapabilityCOmponent is not possible . this is FATAL"),*GetName());
	}

}

/**Before calling this . check for validity in caller function using the CanQueryMoveState() virtual function , override with functionality if necessary*/
bool AMainSquadCharacter::IsMoving()
{
	if(AAIController* CurController = Cast<AAIController>(GetController()))
	{
		return !(CurController->GetMoveStatus() == EPathFollowingStatus::Idle);
	}

	return false;
}

bool AMainSquadCharacter::CanQueryMoveState()
{
	return Cast<AAIController>(GetController());
}


void AMainSquadCharacter::OnPickUpItem(const ABaseItem* ItemToPickUp) //FIXME rename this to OnEquipItem
{
	//WARNING this interface implementation is called by the pickup capability component and should not be called explicitly to avoid recursions

	ABaseItem* ItemPtr = const_cast<ABaseItem*>(ItemToPickUp);
	if(ABaseWeapon* Weapon = Cast<ABaseWeapon>(ItemPtr))
	{

		//hiding and handling currently held weapon is handled by the pickup component
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Attempting to Attach to Weapon Socket %s"),*GetName(),*Weapon->GetName());
		FString IsHiddenStr = (Weapon->IsHidden() ? "true" : "false");
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Weapon Hidden state for %s is %s"),*GetName(),*Weapon->GetName(),*IsHiddenStr);

		
		Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,WeaponMainSocketName);
		
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to pick up something that is not pickable or is a null pointer , this is not good"),*GetName())
		//else if ABaseCannon ? etc.etc.etc.
	}
}

void AMainSquadCharacter::OnDropItem(const ABaseItem* ItemToDrop)
{
	//WARNING this interface implementation is called by the pickup capability component and should not be called explicitly to avoid recursions

	ABaseItem* ItemPtr = const_cast<ABaseItem*>(ItemToDrop);
	if(ABaseWeapon* Weapon = Cast<ABaseWeapon>(ItemPtr))
	{

		//hiding and handling currently held weapon is handled by the pickup component
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Attempting to Drop to Weapon %s"),*GetName(),*Weapon->GetName());
		FString IsHiddenStr = (Weapon->IsHidden() ? "true" : "false");
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Weapon Hidden state for %s is %s"),*GetName(),*Weapon->GetName(),*IsHiddenStr);

		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to pick up something that is not droppable or is a null pointer , this is not good"),*GetName())
		//else if ABaseCannon ? etc.etc.etc.
	}
}


void AMainSquadCharacter::OnStowItem(const ABaseItem* ItemToStow)
{
	//WARNING this interface implementation is called by the pickup capability component and should not be called explicitly to avoid recursions

	ABaseItem* ItemPtr = const_cast<ABaseItem*>(ItemToStow);
	if(ABaseWeapon* Weapon = Cast<ABaseWeapon>(ItemPtr))
	{

		//hiding and handling currently held weapon is handled by the pickup component
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Attempting to Stow Weapon %s"),*GetName(),*Weapon->GetName());
		const FString IsHiddenStr = (Weapon->IsHidden() ? "true" : "false");
		UE_LOG(LogAlifDebug, Display, TEXT("%s : Weapon Hidden state for %s is %s"),*GetName(),*Weapon->GetName(),*IsHiddenStr);
		
		Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,BackpackSocketName);//FIXME BaseItem should have FUnction to get default Transform fro mDefault CDO as wel as "stow" transform


	}else
	{
		UE_LOG(LogAlifDebug, Error, TEXT("%s : Attempting to pick up something that is not stowable or is a null pointer , this is not good"),*GetName())
		//else if ABaseCannon ? etc.etc.etc.
	}
}

bool AMainSquadCharacter::TriggerWeaponSwitch()
{
	UE_LOG(LogAlifDebug,Warning,TEXT("Attempting to switch weapon for %s"),*GetName());

	if(HasInventoryCapability())
	{
		return InventoryCapabilityComp->SwitchToNextWeapon();
	}
	else
	{
		UE_LOG(LogAlifDebug,Error,TEXT("Attempting to switch weapon on a character with no inventory capability this is fatal : %s"),*GetName())
	}

	return false;
}
//End Interface Implementation