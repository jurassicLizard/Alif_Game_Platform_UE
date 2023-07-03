// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupCapabilityComponent.generated.h"


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




private:

	FString DefaultWeaponSocket;

public:
	
	UFUNCTION()
	FString& GetWeaponSocket() {return DefaultWeaponSocket;}
	void SetWeaponSocket(const FString& NewSocketName) {DefaultWeaponSocket = NewSocketName;}

		
	
};
