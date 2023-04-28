// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput/SelectAction.h"

#include "InputActionValue.h" 
#include "InputTriggers.h"

USelectAction::USelectAction()
{
    ValueType = EInputActionValueType::Boolean;

    //Adding a trigger and setting the actuation value (trigger only once)
    PressedTrigger = CreateDefaultSubobject<UInputTriggerPressed>(TEXT("Pressed Trigger"));
    PressedTrigger->ActuationThreshold = 0.1f;
    Triggers.AddUnique(PressedTrigger);
    
}
