// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainSquad/MainSquadCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Items/Weapons/Rifles/PrototypeRifle.h"
#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"
#include "Characters/CapabilityComponents/PickupCapabilityComponent.h"




AMainSquadCharacter::AMainSquadCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
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
		UE_LOG(LogTemp, Error, TEXT("%s : Getting a null pointer instead of our capsule component, something really terrible is happening here"),*GetName());
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
		UE_LOG(LogTemp, Warning, TEXT("%s : is NOT alive and ticking "),*GetName());
	}

	if(USkeletalMeshComponent* CharMesh = GetMesh())
	{
		if(!GetWorld()) 
		{
			UE_LOG(LogTemp, Error, TEXT("Something terrible has happend the world hasnot be created yet : %s"),*GetName());
			return;
		}

		//Hide existing weapon we dont want
		CharMesh->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);



		if(HasInventoryCapability())
		{
					UE_LOG(LogTemp, Warning, TEXT("Has Inventory Attempting to populate : %s"),*GetName());
					bool bSuccessAdd = GetInventoryCapabilityComponent()->AddMainWeaponToInventory(GetWorld()->SpawnActor<APrototypeRifle>(APrototypeRifle::StaticClass()));

					if(bSuccessAdd)
					{
							
						TWeakObjectPtr<ABaseWeapon> MainWeaponObj = GetInventoryCapabilityComponent()->GetMainWeapon();

						if(MainWeaponObj.IsValid())
						{
							MainWeaponObj->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponRSocket"));
						}else
						{
							UE_LOG(LogTemp, Error, TEXT("We have a null pointer mesh at %s"),*GetName());
							UE_LOG(LogTemp, Error, TEXT("%s : Current Weapon inventory size is %d"),*GetName(),GetInventoryCapabilityComponent()->GetWeaponInventorySize())
						}
					}else
					{
						UE_LOG(LogTemp, Error, TEXT("%s : Failed to Add Main Weapon"));
					}


		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : Has no Inventory"),*GetName());
		}

		
		

	}else
	{
		UE_LOG(LogTemp, Error, TEXT("We have a null pointer mesh at %s"),*GetName());
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
	UE_LOG(LogTemp, Warning, TEXT("%s reports being selected"),*GetName());
}

void AMainSquadCharacter::OnPrimaryActionTrigger(FVector NewLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("%s reports attempting to move"),*GetName());

	//TODO make sure AIController is always Created

	if(AAIController* Controller = Cast<AAIController>(GetController()))
	{
		Controller->MoveToLocation(NewLocation);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no AI Controller and cannot be controlled , this is fatal"),*GetName());
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
		UE_LOG(LogTemp, Error, TEXT("%s : Implementing PickupCapabilityInterface but having no PickupCapabilityCOmponent is not possible . this is FATAL"),*GetName());
	}

}
void AMainSquadCharacter::OnCancelledPickupCmd()
{
	if(HasPickupCapability())
	{
		PickupCapabilityComp->CancelPickupCommand();
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Implementing PickupCapabilityInterface but having no PickupCapabilityCOmponent is not possible . this is FATAL"),*GetName());
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
//End Interface Implementation