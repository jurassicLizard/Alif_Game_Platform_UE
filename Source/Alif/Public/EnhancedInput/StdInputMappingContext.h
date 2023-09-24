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
class USwitchWeaponAction;


UCLASS()
class ALIF_API UStdInputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()

//Begin Class Interface

public:
	UStdInputMappingContext();
//End Class Interface


private:

	UPROPERTY()
    const ULookAction* LookAction;
	UPROPERTY()
	const UZoomAction* ZoomAction;
	UPROPERTY()
	const USelectAction* SelectAction;
	UPROPERTY()
	const UReleaseAction* ReleaseAction;
	UPROPERTY()
	const USwitchWeaponAction* SwitchWeaponAction;





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
	UFUNCTION()
	USwitchWeaponAction* GetSwitchWeaponAction() const{return const_cast<USwitchWeaponAction*>(SwitchWeaponAction);}
	
	
	
	
};
