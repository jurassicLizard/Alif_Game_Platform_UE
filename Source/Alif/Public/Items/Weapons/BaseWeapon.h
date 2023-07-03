// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
	


protected:

	virtual bool IsWeapon() override {return true;}
	
	
};
