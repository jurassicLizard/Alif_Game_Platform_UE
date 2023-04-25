// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "StdInputMappingContext.generated.h"

/**
 * 
 */
class ULookAction;
class UZoomAction;
class USelectAction;
class UReleaseAction;

UCLASS()
class ALIF_API UStdInputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()

//Begin Class Interface

public:
	UStdInputMappingContext();
//End Class Interface


private:

    const ULookAction* LookAction;
    const UZoomAction* ZoomAction;
    const USelectAction* SelectAction;
    const UReleaseAction* ReleaseAction;





//public access section

public:

	UFUNCTION()
	ULookAction*  GetLookAction() const {return const_cast<ULookAction*>(LookAction);}
	UFUNCTION()
	UZoomAction*  GetZoomAction() const {return const_cast<UZoomAction*>(ZoomAction);};
	UFUNCTION()
	USelectAction*  GetSelectAction() const {return const_cast<USelectAction*>(SelectAction);};
	UFUNCTION()
	UReleaseAction*  GetReleaseAction() const {return const_cast<UReleaseAction*>(ReleaseAction);};
	
	
	
	
};
