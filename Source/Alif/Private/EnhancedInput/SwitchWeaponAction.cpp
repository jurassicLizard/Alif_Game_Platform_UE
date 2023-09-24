// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput/SwitchWeaponAction.h"




USwitchWeaponAction::USwitchWeaponAction()
{
	ValueType = EInputActionValueType::Boolean;

	PressedTrigger = CreateDefaultSubobject<UInputTriggerPressed>(TEXT("Pressed Triggeer"));
	PressedTrigger->ActuationThreshold = 0.1f;
	Triggers.AddUnique(PressedTrigger);
	
}
