// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/MainSpectatorPawn.h"
#include "AlifLogging.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "Characters/CapabilityComponents/InventoryCapabilityComponent.h"

#include "Pawns/MainSpectatorPawnMovement.h"
#include "Pawns/MainCameraComponent.h"
#include "Controllers/MainPlayerController.h"	
#include "EnhancedInput/StdInputMappingContext.h"
#include "EnhancedInput/LookAction.h"
#include "EnhancedInput/ZoomAction.h"
#include "EnhancedInput/SelectAction.h"
#include "EnhancedInput/ReleaseAction.h"
#include "EnhancedInput/SwitchWeaponAction.h"
#include "Interfaces/InventoryCapabilityInterface.h"


AMainSpectatorPawn::AMainSpectatorPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UMainSpectatorPawnMovement>(Super::MovementComponentName)), 
    StandardPlayMappingContext(GetMutableDefault<UStdInputMappingContext>()) //TODO change this to be called from StdInputMappingContext on Demand
{
    PrimaryActorTick.bCanEverTick = false;

    //Construct Pawn Elements and set default parameters
    GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    bAddDefaultMovementBindings = false;
    MainCameraComponent = CreateDefaultSubobject<UMainCameraComponent>(TEXT("MainCameraComponent"));
    MainCameraComponent->SetupAttachment(GetRootComponent());


    if(StandardPlayMappingContext)
    {
        LookAction    = StandardPlayMappingContext->GetLookAction();
        ZoomAction    = StandardPlayMappingContext->GetZoomAction();
        SelectAction  = StandardPlayMappingContext->GetSelectAction();
        ReleaseAction = StandardPlayMappingContext->GetReleaseAction();
        SwitchWeaponAction = StandardPlayMappingContext->GetSwitchWeaponAction();
    }

}

//Superclass override
void AMainSpectatorPawn::BeginPlay()
{
    Super::BeginPlay();

    //Setup Enhanced Input System Mapping Context
    if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if(PlayerController->GetLocalPlayer())
        {
            if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->AddMappingContext(StandardPlayMappingContext,0);
            }

        }

    }


    
}

//Superclass override
void AMainSpectatorPawn::SetupPlayerInputComponent(UInputComponent *InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    //Setup Enhanced Input System Action bindings

    if(LookAction == nullptr ||
        ZoomAction == nullptr)
    {
        UE_LOG(LogAlifDebug, Error, TEXT("We Cannot Move / Only Partially move. this is fatal"));
    }

    
    if(SelectAction == nullptr ||
        ReleaseAction == nullptr)
    {
        UE_LOG(LogAlifDebug, Error, TEXT("We Cannot use any selection or release options. this is fatal"));
    }

    if(SwitchWeaponAction == nullptr)
    {
        UE_LOG(LogAlifDebug,Fatal, TEXT("We cannot switch weapons , this is fatal"));
    }

 

    if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::TriggerMove2D);
        EnhancedInputComponent->BindAction(ZoomAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::TriggerZoom);
        EnhancedInputComponent->BindAction(SelectAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::OnMouseLeft);
        EnhancedInputComponent->BindAction(ReleaseAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::OnMouseRight);
        EnhancedInputComponent->BindAction(SwitchWeaponAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::OnSwitchWeapon);
        
    }



}

void AMainSpectatorPawn::TriggerMove2D(const FInputActionValue& Value)
{
    FVector2D MouseXY = Value.Get<FVector2D>();
        
    if (MainCameraComponent)
    {
        if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
        {
            if (!PlayerController->bShowMouseCursor)
            {
                MainCameraComponent->Move2D(MouseXY);

            }

        }
    }

}

void AMainSpectatorPawn::TriggerZoom(const FInputActionValue& Value)
{
    float MouseWheelVal = Value.Get<float>();

    if(MainCameraComponent)
    {
         (MouseWheelVal > 0) ? MainCameraComponent->TriggerZoomIn() : MainCameraComponent->TriggerZoomOut();
    }


}

void AMainSpectatorPawn::OnMouseLeft(const FInputActionValue& Value)
{
    if(AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
    {
        if (!PlayerController->IsActorSelected())
        {
            PlayerController->SelectActorUnderCursor();
        }else
        {
            PlayerController->HandleSelectedActorAction(EMPCActionTypes::PRIMARY);

        }

    }
}

void AMainSpectatorPawn::OnMouseRight(const FInputActionValue& Value)
{
    if(AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
    {
        PlayerController->ClearActorSelection();


    }
}



void AMainSpectatorPawn::OnMouseScrollUp()
{  
    if(MainCameraComponent)
    {
        MainCameraComponent->TriggerZoomIn();
    }
    
}

void AMainSpectatorPawn::OnMouseScrollDown()
{
    if(MainCameraComponent)
    {
        MainCameraComponent->TriggerZoomOut();
    }
}

void AMainSpectatorPawn::OnSwitchWeapon()
{
    if(const AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
    {
        if(AActor* SelectedActor = PlayerController->GetCurSelectedActor().Get())
        {
            //get selected actor inventory and call switch method
            if(SelectedActor->GetClass()->ImplementsInterface(UInventoryCapabilityInterface::StaticClass()))
            {
                UE_LOG(LogAlifDebug,Display,TEXT("Attempting to Switch Weapon for %s"),*SelectedActor->GetName());
                IInventoryCapabilityInterface* SelectedActorInvIface = Cast<IInventoryCapabilityInterface>(SelectedActor);
                SelectedActorInvIface->SwitchToNextWeapon(); //FIXME this is wrong we should call InitiateSwitchToNextWeapon and rename SwitchToNextWeapon to OnSwitchToNextWeapon
                
            }
            //call switch on actor inventory
            
        }
    }
}


UMainCameraComponent *AMainSpectatorPawn::GetMainCameraComponent()
{
    return MainCameraComponent;
}
