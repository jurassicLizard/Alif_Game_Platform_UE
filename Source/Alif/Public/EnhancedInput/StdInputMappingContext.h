// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "StdInputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API UStdInputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()

//Begin Class Interface

public:
	UStdInputMappingContext();
//End Class Interface


protected:

   void AddInputActionToContext(UInputAction* InputAction);



	
	
	
};
