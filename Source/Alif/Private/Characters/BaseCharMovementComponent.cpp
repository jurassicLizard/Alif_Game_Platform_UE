// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharMovementComponent.h"





UBaseCharMovementComponent::UBaseCharMovementComponent(const FObjectInitializer &ObjectInitializer)
{
    //we set this so that our animation works properly . we need to call Super(SetDefaultSubobjectClass<UMainSpectatorPawnMovement>(Super::MovementComponentName)))
    //on Our Character Constructor so that we can override the movement component
    bUseAccelerationForPaths = true;
}
