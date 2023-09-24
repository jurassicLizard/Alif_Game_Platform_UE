// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API UBaseCharMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	

public:
	UBaseCharMovementComponent(const FObjectInitializer& ObjectInitializer);
	
	
};
