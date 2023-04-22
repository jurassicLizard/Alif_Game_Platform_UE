// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "MainSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API AMainSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	AMainSpectatorPawn(const FObjectInitializer& ObjectInitializer);

	// /** event call on move forward input */
	// virtual void MoveForward(float Val) override;

	// /** event call on strafe right input */
	// virtual void MoveRight(float Val) override;

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera Actor", meta = (AllowPrivateAccess = "true"))
	class UMainCameraComponent* MainCameraComponent;

public:

	/** Handles the mouse scrolling up*/
	void OnMouseScrollUp();

	/** Handles the mouse scrolling down*/
	void OnMouseScrollDown();


	/** Returns a pointer to the camera component the pawn has*/
	UMainCameraComponent* GetMainCameraComponent();


	


	
	
	
	
};
