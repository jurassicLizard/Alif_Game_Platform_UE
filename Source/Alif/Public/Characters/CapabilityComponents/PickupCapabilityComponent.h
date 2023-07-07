// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupCapabilityComponent.generated.h"


UENUM()
enum class EPickupCmdState : uint8
{
	NONE = 0,
	PENDING,
	CANCELLING,
	FINALIZING,
	MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALIF_API UPickupCapabilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupCapabilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//BEGIN INTERFACE

private:
	EPickupCmdState PickupCmdState;
	UPROPERTY()
	class ABaseItem* PendingItemToPickUp;
	bool bIsValidComponentUse;

private:
	bool ValidateUseableState();
	/**Complete and reset transitions are private due to the fact that Queue and cancel transition to them and so are sufficient for access from other classes*/
	void CompletePickupCommand();
	void ResetPickupCommand();

public:
	UFUNCTION()
	void QueuePickupCommand(const ABaseItem* PendingItemToPickUpNew);
	void CancelPickupCommand();
	EPickupCmdState GetPickupCmdState() const {return PickupCmdState;}
	void SetPickupCmdState(EPickupCmdState NewPickupState) {PickupCmdState = NewPickupState;}



//END INTERFACE


private:

	FString DefaultWeaponSocket;

public:
	
	UFUNCTION()
	FString& GetWeaponSocket() {return DefaultWeaponSocket;}
	UFUNCTION()
	void SetWeaponSocket(const FString& NewSocketName) {DefaultWeaponSocket = NewSocketName;}
	UFUNCTION()
	bool PickUpWeapon(class ABaseWeapon* BaseWeaponOut) const;



		
	
};
