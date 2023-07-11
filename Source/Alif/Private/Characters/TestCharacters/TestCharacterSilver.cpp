// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TestCharacters/TestCharacterSilver.h"
#include "AlifLogging.h"




ATestCharacterSilver::ATestCharacterSilver(const FObjectInitializer& ObjectInitializer):
    Super(ObjectInitializer)
{
    ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSkeletalMeshHelper(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith"));
    ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimationHelper(TEXT("/Game/Characters/Animations/Wraith_AnimBlueprintCustom"));


	if(GetMesh())
	{
        //Set Mesh and animation

		GetMesh()->SetSkeletalMesh(CharacterSkeletalMeshHelper.Object);
        GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
        GetMesh()->SetAnimClass(CharacterAnimationHelper.Class);
	}else
    {
        UE_LOG(LogAlifDebug, Error, TEXT("We are not properly initializing ItemMesh under %s"), *GetName());
    }

    
}


void ATestCharacterSilver::BeginPlay()
{
    Super::BeginPlay();
}

void ATestCharacterSilver::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}