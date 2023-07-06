// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingPickableComponent.generated.h"


class UCapsuleComponent;

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
	UPROPERTY(VisibleDefaultsOnly,Category="Floating Idle Pickable", meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* PickableCapsuleComp;
	FRotator CapsuleWorldRotationOffset;
	FVector CapsuleWorldLocationOffset;
	UPROPERTY()
	EPickedState PickedState;

	




private:

	UFUNCTION()
	float GetTransformedSine();

protected:
	UFUNCTION()
	virtual USceneComponent* GetDesiredParentAttachmentPoint(); //virtual  for portability in order to allow for multi attachment to any item different than ABaseItem
	void AddCapsuleWorldRotationOffset(FRotator WorldRotationOffset = FRotator(0.f,0.f,90.f)); //we provide the opportunity for child classes to override capsule parameters
	void AddCapsuleWorldLocationOffset(FVector WorldLocationOffset = FVector(0.f,25.f,10.f));
	void SetPickableCapsuleHalfHeight(float HalfHeight = 44.f);
	void SetPickableCapsuleRadius(float Radius = 18.f);


public:
	EPickedState& GetPickedState() {return PickedState;};
	void SetPickedState(EPickedState const& NewPickedState) { PickedState = NewPickedState;}




		
	
};
