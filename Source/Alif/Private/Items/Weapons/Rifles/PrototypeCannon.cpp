// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifles/PrototypeCannon.h"
#include "AlifLogging.h"
#include "Components/CapsuleComponent.h"
#include "Items/ItemComponents/FloatingPickableComponent.h"




APrototypeCannon::APrototypeCannon()
{

    ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponSkeletalMeshHelper(TEXT("/Game/AssetPacks/ShooterGame/Weapons/Launcher"));
	if(GetItemMesh())
	{
		GetItemMesh()->SetSkeletalMesh(WeaponSkeletalMeshHelper.Object);
	}else
    {
        UE_LOG(LogAlifDebug, Error, TEXT("We are not properly initializing ItemMesh under %s"), *GetName());
    }

    FloatingPickableComponent = CreateDefaultSubobject<UFloatingPickableComponent>("Floating Idle Pickable Component");
    AddOwnedComponent(FloatingPickableComponent);

    
    
}

