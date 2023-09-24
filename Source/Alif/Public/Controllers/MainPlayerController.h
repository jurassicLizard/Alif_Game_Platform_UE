// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UENUM()
enum class EMPCActionTypes : uint8
{
	PRIMARY = 0,
	SECONDARY,
	TERTIARY,
	MAX


};

UCLASS()
class ALIF_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**Begin Class Interface*/
	AMainPlayerController(const FObjectInitializer& ObjectInitializer);
	/**End Class Interface*/

//begin AController interface
	/** update input detection */
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
//end AController interface

protected:

	void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	TWeakObjectPtr<AActor> CurSelectedActor;
	float PickableSphereTraceRadius;
	FVector PickableSphereTraceZOffset;


private:
	
	UFUNCTION() /*this function sweeps for all actors that have the floatingpickablecomponent . i.e. all actors that are pickable*/
	bool SweepSphereAtLocationForPickables(FHitResult& HitResultOut,FVector SweepLocation);
	UFUNCTION()
	bool CheckIfPickupPossible(AActor const* SelectedActorIn,AActor const* PickupItemIn) const;


//public types

public:



//public class access

public:
	//Begin Actor Selections Markers
	UFUNCTION()
	TWeakObjectPtr<AActor> GetCurSelectedActor() const {return CurSelectedActor;};
	UFUNCTION()
	void SetCurSelectedActor(AActor* const NewActor);
	UFUNCTION()
	void ClearActorSelection(){CurSelectedActor = nullptr;};
	bool IsActorSelected() const {return (CurSelectedActor != nullptr);}

	//End Actor Selections Markers

	//Begin Actor Actions
	UFUNCTION()
	void SelectActorUnderCursor();
	UFUNCTION()
	bool SelectActorUnderCursorBySweep();
	UFUNCTION()
	void HandleSelectedActorAction(EMPCActionTypes ActionType);
	//End Actor Actions







	
	
	
	
};





