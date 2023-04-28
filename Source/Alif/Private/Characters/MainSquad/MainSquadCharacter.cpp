// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainSquad/MainSquadCharacter.h"
#include "Components/CapsuleComponent.h"




AMainSquadCharacter::AMainSquadCharacter()
{
    //set primary capsule collision component settings
	GetCapsuleComponent()->SetCapsuleHalfHeight(93.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.78f);

	//Set the location and rotation of the Character Mesh Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -94.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));


}
