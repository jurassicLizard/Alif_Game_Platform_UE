// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/SharedPointer.h"

#include "InventoryCapabilityComponent.generated.h"


class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALIF_API UInventoryCapabilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryCapabilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	uint8 MaxWeapons = 30;
	UPROPERTY()
	TArray<ABaseWeapon*> WeaponsInventoryArray; //update MaxWeapons for more efficiency in case our weapons exceed 30




public:

	UFUNCTION()
	ABaseWeapon* GetWeaponAt(int32 Idx)  const;
	UFUNCTION()
	ABaseWeapon* GetMainWeapon() const{return GetWeaponAt(0);}
	UFUNCTION()
	ABaseWeapon* GetSecondaryWeapon() const{return GetWeaponAt(1);}
	UFUNCTION()
	bool AddWeaponToInventoryAtIdx(ABaseWeapon const* NewBaseWeapon,int32 Idx); //This add is unique
	UFUNCTION()
	bool AddMainWeaponToInventory(ABaseWeapon const* NewBaseWeapon) {return AddWeaponToInventoryAtIdx(NewBaseWeapon,0);}
	UFUNCTION()
	bool AddSecondaryWeaponToInventory(ABaseWeapon const* NewBaseWeapon){ return AddWeaponToInventoryAtIdx(NewBaseWeapon,1);}
	UFUNCTION()
	bool RemoveWeaponFromInventory(ABaseWeapon const* DeletedBaseWeapon){return (WeaponsInventoryArray.Remove(const_cast<ABaseWeapon*>(DeletedBaseWeapon)) != 0);}
	UFUNCTION()
	int32 GetWeaponInventorySize() const{return WeaponsInventoryArray.Num();}

	



		
	
};
