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
	AMainPlayerController();
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


//public types

public:



//public class access

public:
	//Begin Actor Selections Markers
	UFUNCTION()
	TWeakObjectPtr<AActor> GetCurSelectedActor() const {return CurSelectedActor;};
	void SetCurSelectedActor(AActor* const NewActor);
	void ClearActorSelection(){CurSelectedActor = nullptr;};
	bool IsActorSelected() const {return (CurSelectedActor != nullptr);}

	//End Actor Selections Markers

	//Begin Actor Actions
	void SelectActorUnderCursor();
	void HandleSelectedActorAction(EMPCActionTypes ActionType);
	//End Actor Actions







	
	
	
	
};





