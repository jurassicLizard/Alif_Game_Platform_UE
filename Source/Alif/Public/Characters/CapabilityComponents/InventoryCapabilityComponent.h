// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryCapabilityComponent.generated.h"


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
	TArray<class ABaseWeapon*> WeaponsInventoryArray; //update MaxWeapons for more efficiency in case our weapons exceed 30




public:

	UFUNCTION()
	ABaseWeapon* GetWeaponAt(int32 Idx)  const { return ((WeaponsInventoryArray.IsValidIndex(Idx)) ?  WeaponsInventoryArray[Idx] :  nullptr);}

	UFUNCTION()
	bool AddWeaponToInventoryAtIdx(ABaseWeapon* NewBaseWeapon,int32 Idx); //This add is unique
	bool RemoveWeaponFromInventory(ABaseWeapon* DeletedBaseWeapon){return (WeaponsInventoryArray.Remove(DeletedBaseWeapon) != 0);}
	



		
	
};
