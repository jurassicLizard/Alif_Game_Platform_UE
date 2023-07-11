// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifles/PrototypeRifle.h"
#include "Items/ItemComponents/FloatingPickableComponent.h"
#include "AlifLogging.h"



APrototypeRifle::APrototypeRifle()
{
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleSkeletalMeshHelper(TEXT("/Game/AssetPacks/ShooterGame/Weapons/Rifle"));
	if(GetItemMesh())
	{
		GetItemMesh()->SetSkeletalMesh(RifleSkeletalMeshHelper.Object);
	}else
    {
        UE_LOG(LogAlifDebug, Error, TEXT("We are not properly initializing ItemMesh under %s"), *GetName());
    }

    FloatingPickableComponent = CreateDefaultSubobject<UFloatingPickableComponent>("Floating Idle Pickable Component");
    AddOwnedComponent(FloatingPickableComponent);
	
}


