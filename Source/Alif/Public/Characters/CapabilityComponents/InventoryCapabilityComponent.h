// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/SharedPointer.h"

#include "InventoryCapabilityComponent.generated.h"


class ABaseWeapon;
class ABaseItem;
class IPickupCapabilityInterface;

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

	UPROPERTY()
	TArray<ABaseWeapon*> WeaponsInventoryArray;
	UPROPERTY()
	ABaseItem* ItemPendingStowAwayAction;
	UPROPERTY()
	ABaseItem* ItemPendingDropAction;

private:

	UFUNCTION()
	bool RemoveWeaponFromInventory(ABaseWeapon const* DeletedBaseWeapon){return (WeaponsInventoryArray.Remove(const_cast<ABaseWeapon*>(DeletedBaseWeapon)) != 0);}
	UFUNCTION()
	bool RemoveWeaponFromInvAndDestroy(ABaseWeapon* DeletedBaseWeapon);
	UFUNCTION()
	bool AddWeaponToInventoryAtIdx(ABaseWeapon const* NewBaseWeapon,int32 Idx); //This add is unique // we need to keep this private since this add is unchecked so we use it internally only
	/**
	 * @brief cycle weapons in inventory making the second weapon as main weapon and main weapon as last
	 *
	 * this also shifts all weapons accordingly in the array and returns a pointer to the new main weapon
	 * @return ABaseWeapon* as new main weapon
	 */
	UFUNCTION()
	ABaseWeapon* CycleWeaponsInInventory();
	UFUNCTION()
	bool IsMainWeaponIdx(int32 Idx) const {return (Idx == 0);}
	UFUNCTION()
	void ResetAllPendingItemActions();
	UFUNCTION()
	FORCEINLINE TArray<ABaseWeapon*>& GetActiveWeaponInventory() { return WeaponsInventoryArray; }


public:

	UFUNCTION()
	ABaseWeapon* GetWeaponAt(int32 Idx)  const;
	UFUNCTION()
	ABaseWeapon* GetMainWeapon() const{return GetWeaponAt(0);}
	UFUNCTION()
	ABaseWeapon* GetSecondaryWeapon() const{return GetWeaponAt(1);}
	UFUNCTION()
	bool AddMainWeaponToInventory(ABaseWeapon const* NewBaseWeapon);
	UFUNCTION()
	bool AddSecondaryWeaponToInventory(ABaseWeapon const* NewBaseWeapon){ return AddWeaponToInventoryAtIdx(NewBaseWeapon,1);}
	UFUNCTION()
	int32 GetWeaponInventorySize() const{return WeaponsInventoryArray.Num();}
	UFUNCTION()
	uint8 GetMaxWeaponInventorySize() const;
	UFUNCTION()
	bool HasRemainingInventoryCapacity() const;
	UFUNCTION()
	ABaseWeapon* GetLastWeapon() const{return ((WeaponsInventoryArray.Num() > 0) ? WeaponsInventoryArray.Top() : nullptr);}
	UFUNCTION()
	bool HasWeaponOfSameTypeInInventory(ABaseWeapon* WeaponToCheck) const;
	UFUNCTION()
	bool SwitchToNextWeapon();


	



		
	
};
