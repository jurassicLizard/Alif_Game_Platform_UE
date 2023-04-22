// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/MainSpectatorPawn.h"

#include "Components/SphereComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 


#include "Pawns/MainSpectatorPawnMovement.h"
#include "Pawns/MainCameraComponent.h" 	
#include "EnhancedInput/StdInputMappingContext.h"
#include "EnhancedInput/LookAction.h"









AMainSpectatorPawn::AMainSpectatorPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UMainSpectatorPawnMovement>(Super::MovementComponentName)), 
    StandardPlayMappingContext(GetMutableDefault<UStdInputMappingContext>()), //TODO change this to be called from StdInputMappingContext on Demand
    LookAction(GetMutableDefault<ULookAction>())
{
    PrimaryActorTick.bCanEverTick = false;

    //Construct Pawn Elements and set default parameters
    GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    bAddDefaultMovementBindings = false;
    MainCameraComponent = CreateDefaultSubobject<UMainCameraComponent>(TEXT("MainCameraComponent"));
    MainCameraComponent->SetupAttachment(GetRootComponent());
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

    if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AMainSpectatorPawn::Move2D);

         UE_LOG(LogTemp, Warning, TEXT("Was able to bind Look Action"));
        
    }



}

void AMainSpectatorPawn::Move2D(const FInputActionValue& Value)
{
    FVector2D MouseXY = Value.Get<FVector2D>();
    UE_LOG(LogTemp, Warning, TEXT("Triggering move2d function %X : %f, Y: %f"),MouseXY.X,MouseXY.Y);
}
void AMainSpectatorPawn::OnMouseScrollUp()
{
    
}

void AMainSpectatorPawn::OnMouseScrollDown()
{
    //TODO Add OnZoomIn Functionality from Camera Component
}

UMainCameraComponent *AMainSpectatorPawn::GetMainCameraComponent()
{
    return MainCameraComponent;
}
