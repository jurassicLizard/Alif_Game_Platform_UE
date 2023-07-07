// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MainSquad/MainSquadCharacter.h"
#include "TestCharacterSilver.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API ATestCharacterSilver : public AMainSquadCharacter
{
	GENERATED_BODY()
	
public:

	ATestCharacterSilver(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	
};
