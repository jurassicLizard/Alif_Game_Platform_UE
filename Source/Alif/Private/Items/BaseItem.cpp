// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"


// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BaseItemRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(BaseItemRootComp);
	BaseItemSkelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Item Skeletal Mesh"));
	BaseItemSkelMeshComp->SetupAttachment(BaseItemRootComp);
;
	
	


}


