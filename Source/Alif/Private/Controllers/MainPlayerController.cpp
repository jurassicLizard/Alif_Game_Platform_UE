// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainPlayerController.h"
#include "Pawns/MainSpectatorPawn.h"
#include "Pawns/MainCameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/SelectableActorInterface.h"



AMainPlayerController::AMainPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
}


void AMainPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    

}

void AMainPlayerController::SelectActorUnderCursor()
{
    FHitResult HitResult;
    if(GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult))
    {
        SetCurSelectedActor(HitResult.GetActor());
    }
    // DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.f,12,FColor::Red,false);
}

bool AMainPlayerController::SelectActorUnderCursorBySweep()
{
    //we only sweep if we have a cursor visibility hit
    FHitResult HitResultCursor;
    if(GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResultCursor))
    {
            if(GetWorld())
            {
            // DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.f,12,FColor::Red,false);

            //conduct sphere trace
            //if colloding with curselected actor ignore
            //else if colliding with other actor
            }

    }

    return false;

}
void AMainPlayerController::HandleSelectedActorAction(EMPCActionTypes ActionType )
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);

    ISelectableActorInterface* SelActor = Cast<ISelectableActorInterface>(GetCurSelectedActor());
    if(!SelActor)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has a fatal nullpointer exception, we are selecting something that doesnot implement a selectable interface"),*GetName());
        return;
    }

    if(EMPCActionTypes::PRIMARY == ActionType)
    {
        //we can only select actors that implement the ISelectableActorInterface nonethelsess we checked above for nullptr
        // DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.f,12,FColor::Red,false,5.f);

        SelActor->OnPrimaryActionTrigger(HitResult.ImpactPoint);

    }
}

void AMainPlayerController::SetCurSelectedActor(AActor *const NewActor)
{
    if(NewActor && 
        NewActor->GetClass()->ImplementsInterface(USelectableActorInterface::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempting to select %s"),*NewActor->GetActorNameOrLabel());  
        ISelectableActorInterface* SelActor = Cast<ISelectableActorInterface>(NewActor);
        if(SelActor)
        {
            SelActor->OnSelectionGained();
            CurSelectedActor = NewActor;
        }
        
      
    }else
    {
        //TODO if is selected and is moveable then we move the selected pawn to the desired postion
        // else we do nothing , 
    }
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
                        // UE_LOG(LogTemp, Warning, TEXT("We are THere in the Player Controller !"));
                        SpectatorPawn->GetMainCameraComponent()->UpdateCameraMovement(this);

                    }

            }



        }

    }
}

