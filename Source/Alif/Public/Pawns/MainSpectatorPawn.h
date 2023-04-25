// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "InputActionValue.h"
#include "MainSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API AMainSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

// Begin class interface

public:
	AMainSpectatorPawn(const FObjectInitializer& ObjectInitializer);

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

// End class interface


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera Actor", meta = (AllowPrivateAccess = "true"))
	class UMainCameraComponent* MainCameraComponent;

	UPROPERTY()
	class UStdInputMappingContext* StandardPlayMappingContext;
	UPROPERTY()
	class ULookAction* LookAction;
	UPROPERTY()
	class UZoomAction* ZoomAction;
	UPROPERTY()
	class USelectAction* SelectAction;
	class UReleaseAction* ReleaseAction;

	/** Handles the mouse scrolling up*/
	void OnMouseScrollUp();
	/** Handles the mouse scrolling down*/
	void OnMouseScrollDown();



protected:

	void TriggerMove2D(const FInputActionValue& Value);
	void TriggerZoom(const FInputActionValue& Value);



//public access Section
public:
	/** Returns a pointer to the camera component the pawn has*/
	UMainCameraComponent* GetMainCameraComponent();


	


	
	
	
	
};
