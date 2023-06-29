// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "PrototypeRifle.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API APrototypeRifle : public ABaseItem
{
	GENERATED_BODY()
	

public:

	APrototypeRifle();




private:

UPROPERTY()
TWeakObjectPtr<USkeletalMesh> RifleSkeletalMesh;

	
	
};
