// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UInventoryCapabilityComponent;
class UPickupCapabilityComponent;

UCLASS()
class ALIF_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY()
	UInventoryCapabilityComponent* InventoryCapabilityComp;
	UPROPERTY()
	UPickupCapabilityComponent* PickupCapabilityComp;


protected:
	UFUNCTION()
	UInventoryCapabilityComponent* GetInventoryCapabilityComponent() const {return InventoryCapabilityComp;}
	UFUNCTION()
	UPickupCapabilityComponent* GetPickupCapabilityComponent() const{return PickupCapabilityComp;}

public:
	bool HasInventoryCapability() const {return (InventoryCapabilityComp != nullptr);}
	bool HasPickupCapability() const{return (PickupCapabilityComp != nullptr);}


	
	
};
