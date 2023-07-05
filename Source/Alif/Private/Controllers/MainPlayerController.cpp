// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainPlayerController.h"
#include "Pawns/MainSpectatorPawn.h"
#include "Pawns/MainCameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/SelectableActorInterface.h"
#include "Interfaces/PickupCapabilityInterface.h"
#include "Items/BaseItem.h"
#include "Characters/BaseCharacter.h"

#include "DrawDebugHelpers.h"

AMainPlayerController::AMainPlayerController():
    PickableSphereTraceRadius(50.f),
    PickableSphereTraceZOffset(0.f,0.f,200.f)
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


    ISelectableActorInterface* SelActor = Cast<ISelectableActorInterface>(GetCurSelectedActor());
    if(!SelActor)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has a fatal nullpointer exception, we are selecting something that doesnot implement a selectable interface"),*GetName());
        return;
    }else
    {
            if(EMPCActionTypes::PRIMARY == ActionType)
            {
                FHitResult HitResultForMove;
                if(GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResultForMove))
                {
                        //sweep under hitresult for any pickable and if yes take it
                        FHitResult HitResultForPickup;
                        IPickupCapabilityInterface* ActorThatPicksUp = Cast<IPickupCapabilityInterface>(GetCurSelectedActor().Get());

                        if(SweepSphereAtLocation(HitResultForPickup,HitResultForMove.ImpactPoint))
                        {
                            UE_LOG(LogTemp, Warning, TEXT("Hit Result reports following component hit %d"),*HitResultForPickup.GetComponent()->GetName());
                            
                            if(CheckIfPickupPossible(GetCurSelectedActor().Get(),HitResultForPickup.GetActor()))  //if it is . set pick up task as pending on actor
                            {
                                //QueuePickup (due to checks we are sure here that we implement PickupCapabilityInterface at actor level)                             
                                if(ActorThatPicksUp){

                                    //due to checks in CHeckIfPickupPossible  we are sure that the Cast to ABaseItem has worked, hence it is unchecked here

                                    ActorThatPicksUp->OnTriggeredPickupCmd(Cast<ABaseItem>(HitResultForPickup.GetActor()));

                                }else
                                {
                                    UE_LOG(LogTemp, Error, TEXT("%s : This shouldnot happen, somehow we were able to validate implemented interface but cannot cast to it"),*GetName());
                                }

                            }    
                            
                        }else if(ActorThatPicksUp)
                        {

                            //OnCancelPickupCommand because there is a change in move direction or a click somewhere else 
                            ActorThatPicksUp->OnCancelledPickupCmd();

                        }else
                        {
                            UE_LOG(LogTemp, Warning, TEXT("%s : Skipping Pickup for Actor that apparently doesnot support pickup"),*GetName());
                        }
                        //we can only select actors that implement the ISelectableActorInterface nonethelsess we checked above for nullptr
                        //after quering for pickup we move movable actor
                        SelActor->OnPrimaryActionTrigger(HitResultForMove.ImpactPoint);

                }

            }

    }


}

bool AMainPlayerController::CheckIfPickupPossible(AActor const* SelectedActorIn,AActor const* PickupItemIn) const
{
    //we should check before calling this . if SelectedActor is actually Selectable
    ABaseCharacter* SelectedActorPtr = Cast<ABaseCharacter>(const_cast<AActor*>(SelectedActorIn));
    ABaseItem* PickableItemPtr = Cast<ABaseItem>(const_cast<AActor*>(PickupItemIn));

        //check for Item, if item is pickable
    if(PickableItemPtr)
    {
        
        if(SelectedActorPtr && PickableItemPtr->HasPickableCapability())
        {

            if(SelectedActorPtr)
            {

                                                //check for actor if actor can pickup
                if(SelectedActorPtr->HasPickupCapability())
                {
                    if(SelectedActorPtr->GetClass()->ImplementsInterface(UPickupCapabilityInterface::StaticClass()))
                    {
                        return true;
                    }else
                    {
                        UE_LOG(LogTemp, Error, TEXT("%s : Actor has Pickup Capability but doesnot implement Pickup Interface . this is fatal"),*GetName());
                    }

                }

            }else
            {
                UE_LOG(LogTemp, Warning, TEXT("%s : Selected Actor is not a Base Character"),*GetName());
            }

        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("%s : Attempting to pick up item with no pickable capability. skipping"),*GetName());
        }


    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : Attempting to pick up invalid item. can only pickup ABaseItem"),*GetName());
    }


    return false;
}


bool AMainPlayerController::SweepSphereAtLocation(FHitResult& HitResultOut,FVector SweepLocation)
{
    //TODO add simple collision form to cannon / pickable item in order to be able to query sweeps
    if(GetWorld())
    {
        FCollisionShape SphereShape = FCollisionShape::MakeSphere(PickableSphereTraceRadius) ;
        FVector Start = (SweepLocation + PickableSphereTraceZOffset);
        FVector End = SweepLocation;

        DrawDebugPoint(GetWorld(),End,5.f,FColor::Red,false,10.f);
        DrawDebugPoint(GetWorld(),Start,5.f,FColor::Blue,false,10.f);
        DrawDebugSphere(GetWorld(),Start,PickableSphereTraceRadius,12,FColor::Black,false,10.f);

        


        return GetWorld()->SweepSingleByChannel(HitResultOut,Start,End,FQuat::Identity, ECollisionChannel::ECC_Visibility,SphereShape);
        
        

        

    }else
    {
        UE_LOG(LogTemp, Error, TEXT("%s : Fatal Error .The World is not there yet"));
    }



    return false;
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

