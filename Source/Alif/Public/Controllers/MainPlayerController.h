// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**Begin Class Interface*/
	AMainPlayerController();
	/**End Class Interface*/

private:

TWeakObjectPtr<AActor> CurSelectedActor;








//public class access

public:

/**Setters and getters*/
TWeakObjectPtr<AActor> GetCurSelectedActor() const {return CurSelectedActor;};
void SetCurSelectedActor(AActor* NewActor){ CurSelectedActor = NewActor};
void ClearActorSelection(){CurSelectedActor = nullptr;};
/**End Setters and getters*/



	
	
	
	
};
