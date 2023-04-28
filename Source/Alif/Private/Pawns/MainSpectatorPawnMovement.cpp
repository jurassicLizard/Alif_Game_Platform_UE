// Fill out your copyright notice in the Description page of Project Settings.
#include "Pawns/MainSpectatorPawnMovement.h"

#include "Pawns/MainSpectatorPawn.h"
#include "Controllers/MainPlayerController.h"
#include "Pawns/MainCameraComponent.h"



UMainSpectatorPawnMovement::UMainSpectatorPawnMovement(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer), bInitialLocationSet(false)
{
    PrimaryComponentTick.bCanEverTick = true;
    MaxSpeed = 14000.f;
    Acceleration = 5000.f;
    Deceleration = 3000.f;
    
}


void UMainSpectatorPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    
    //FIXME this check is already being performed in Super , do we need it again ?
    // if(!GetPawnOwner() || !UpdatedComponent)
    // {
    //     return;
    // }
    //FIXME EXPERIMENTAL CODE
    // AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetPawnOwner()->GetController());

    // if(PlayerController && PlayerController->IsLocalController())
    // {
    //     //set initial location
    //     if(!bInitialLocationSet)
    //     {
    //         GetPawnOwner()->SetActorLocationAndRotation(PlayerController->GetSpawnLocation(),
    //                                                     PlayerController->GetControlRotation());
    //         bInitialLocationSet = true;
    //     }

    //     FVector MyLocation = UpdatedComponent->GetComponentLocation();
    //     AMainSpectatorPawn* SpectatorPawn = Cast<AMainSpectatorPawn>(GetPawnOwner());

    //     if(SpectatorPawn && SpectatorPawn->GetMainCameraComponent())
    //     {
    //         UE_LOG(LogTemp, Warning, TEXT("We are clamping"));
    //         SpectatorPawn->GetMainCameraComponent()->ClampCameraLocation(PlayerController, MyLocation);
    //     } 
    //     UpdatedComponent->SetWorldLocation(MyLocation,false);
    // }
    //END EXPERIMENTAL CODE


}

