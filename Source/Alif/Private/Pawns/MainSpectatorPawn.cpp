// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MainSpectatorPawn.h"
#include "Pawns/MainSpectatorPawnMovement.h"
#include "Pawns/MainCameraComponent.h" 	


#include "Components/SphereComponent.h"




AMainSpectatorPawn::AMainSpectatorPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UMainSpectatorPawnMovement>(Super::MovementComponentName))
{
    GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    bAddDefaultMovementBindings = false;
    MainCameraComponent = CreateDefaultSubobject<UMainCameraComponent>(TEXT("MainCameraComponent"));
    MainCameraComponent->SetupAttachment(GetRootComponent());
}

void AMainSpectatorPawn::SetupPlayerInputComponent(UInputComponent *InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
}

void AMainSpectatorPawn::OnMouseScrollUp()
{
    //TODO Add OnZoomIn Functionality from Camera Component
}

void AMainSpectatorPawn::OnMouseScrollDown()
{
    //TODO Add OnZoomIn Functionality from Camera Component
}

UMainCameraComponent *AMainSpectatorPawn::GetMainCameraComponent()
{
    return MainCameraComponent;
}
