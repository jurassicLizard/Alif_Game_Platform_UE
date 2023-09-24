// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawnMovement.h"
#include "MainSpectatorPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API UMainSpectatorPawnMovement : public USpectatorPawnMovement
{
	GENERATED_BODY()

public:

	UMainSpectatorPawnMovement(const FObjectInitializer& ObjectInitializer);
	/**Begin Class Interface*/


	virtual void TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction *ThisTickFunction) override;

	/**End Class Interface*/
	
	
private:
	bool bInitialLocationSet = false;
	
};
