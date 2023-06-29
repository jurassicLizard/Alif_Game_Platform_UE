// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifles/PrototypeRifle.h"



APrototypeRifle::APrototypeRifle()
{
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleSkeletalMeshHelper(TEXT("/Game/AssetPacks/ShooterGame/Weapons/Rifle"));
	RifleSkeletalMesh = RifleSkeletalMeshHelper.Object;
	BaseItemSkelMeshComp->SetSkeletalMesh(RifleSkeletalMesh.Get());
}
