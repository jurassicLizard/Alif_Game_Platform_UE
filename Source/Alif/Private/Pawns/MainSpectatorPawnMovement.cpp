// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MainSpectatorPawnMovement.h"



UMainSpectatorPawnMovement::UMainSpectatorPawnMovement(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer), bInitialLocationSet(false)
{
    MaxSpeed = 14000.f;
    Acceleration = 5000.f;
    Deceleration = 3000.f;
}


void UMainSpectatorPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    if(!GetOwner() || !UpdatedComponent)
    {
        return;
    }


}

