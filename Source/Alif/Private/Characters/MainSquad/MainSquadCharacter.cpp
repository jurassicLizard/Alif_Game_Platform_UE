// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainSquad/MainSquadCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Items/Weapons/Rifles/PrototypeRifle.h"





AMainSquadCharacter::AMainSquadCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
    //set primary capsule collision component settings
	GetCapsuleComponent()->SetCapsuleHalfHeight(93.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.78f);

	//Set the location and rotation of the Character Mesh Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -94.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));


}

void AMainSquadCharacter::BeginPlay()
{
	Super::BeginPlay();
	//temporary code specific to wraith character
	
	if(USkeletalMeshComponent* CharMesh = GetMesh())
	{
		CharMesh->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
		MainWeaponObj = GetWorld()->SpawnActor<APrototypeRifle>(APrototypeRifle::StaticClass());
		if(MainWeaponObj.IsValid())
		{
			MainWeaponObj->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponRSocket"));
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("We have a null pointer mesh at %s"),*GetName());
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
		 	GEngine->AddOnScreenDebugMessage(3,GetWorld()->GetDeltaSeconds(), FColor::Blue, FString::Printf(TEXT("Acceleration Value : %f"), MoveComp->GetCurrentAcceleration().Size()));

		}


		GEngine->AddOnScreenDebugMessage(5,GetWorld()->GetDeltaSeconds(), FColor::Blue, FString::Printf(TEXT("Velocity Value : %f"), Velocity.Size()));

		 GEngine->AddOnScreenDebugMessage(4,GetWorld()->GetDeltaSeconds(), FColor::Blue, FString::Printf(TEXT("TestVector Value : %f"), TestVector.Size()));

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
//End Interface Implementation