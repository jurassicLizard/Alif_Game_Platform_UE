// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "PrototypeCannon.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API APrototypeCannon : public ABaseWeapon
{
	GENERATED_BODY()
	
	
public:

	APrototypeCannon();
	

public:
	UFUNCTION()
	const UFloatingPickableComponent* GetFloatingPickableComponent() const {return FloatingPickableComponent;};

};
