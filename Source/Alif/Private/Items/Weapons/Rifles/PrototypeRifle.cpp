// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifles/PrototypeRifle.h"



APrototypeRifle::APrototypeRifle()
{
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleSkeletalMeshHelper(TEXT("/Game/AssetPacks/ShooterGame/Weapons/Rifle"));
	if(GetItemMesh())
	{
		GetItemMesh()->SetSkeletalMesh(RifleSkeletalMeshHelper.Object);
	}else
    {
        UE_LOG(LogTemp, Error, TEXT("We are not properly initializing ItemMesh under %s"), *GetName());
    }

	
}


