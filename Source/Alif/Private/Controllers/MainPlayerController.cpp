// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainPlayerController.h"
#include "Pawns/MainSpectatorPawn.h"
#include "Pawns/MainCameraComponent.h"




AMainPlayerController::AMainPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
}


void AMainPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
    Super::PostProcessInput(DeltaTime,bGamePaused);

    if(!bGamePaused)
    {
        if(GetLocalPlayer())
        {
            AMainSpectatorPawn* SpectatorPawn = Cast<AMainSpectatorPawn>(GetPawnOrSpectator());

            if(SpectatorPawn)
            {
                    //TODO add minimap bounds through minimap hud

                    //TODO handle GameState changes
                    const bool bIsGameStateValid = true;

                    if(bIsGameStateValid)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("We are THere in the Player Controller !"));
                        SpectatorPawn->GetMainCameraComponent()->UpdateCameraMovement(this);

                    }

            }



        }

    }
}

