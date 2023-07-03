// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingPickableComponent.generated.h"




UENUM()
enum class EPickedState : uint8
{
	DROPPED,
	PICKED,
	MAX
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALIF_API UFloatingPickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingPickableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:

	UPROPERTY(VisibleDefaultsOnly,Category="Floating Idle Pickable", meta=(AllowPrivateAccess = "true"))
	float Amplitude;
	UPROPERTY(VisibleDefaultsOnly,Category="Floating Idle Pickable", meta=(AllowPrivateAccess = "true"))
	float TimeConstant;
	UPROPERTY(VisibleDefaultsOnly,Category="Floating Idle Pickable", meta=(AllowPrivateAccess = "true"))
	float RotationSpeed;
	UPROPERTY()
	EPickedState PickedState;




private:

	UFUNCTION()
	float GetTransformedSine();


public:
	EPickedState& GetPickedState() {return PickedState;};
	void SetPickedState(EPickedState const& NewPickedState) { PickedState = NewPickedState;}




		
	
};
