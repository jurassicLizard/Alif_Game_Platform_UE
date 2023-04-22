// Copyright Epic Games, Inc. All Rights Reserved.


#include "AlifGameModeBase.h"
#include "Pawns/MainSpectatorPawn.h"

AAlifGameModeBase::AAlifGameModeBase()
{
    //we dont need this actor to tick 
    PrimaryActorTick.bCanEverTick = false;
    //define UClass defaults for PlayerController, DefaultPawn , SPectator and Game State as well as HUD

    SpectatorClass = AMainSpectatorPawn::StaticClass();
    DefaultPawnClass = AMainSpectatorPawn::StaticClass();


    
    

}

//BEGIN Function overrides from super class
void AAlifGameModeBase::RestartPlayer(AController *NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
}


//End Function overrides from super class


//BEGIN General Game Handling Functions
void AAlifGameModeBase::FinishGame(FString CurrentlyNOTIMPLEMENTED)
{
}

void AAlifGameModeBase::ReturnToMenu()
{
}

void AAlifGameModeBase::ExitGame()
{
}

//End General Game Handling Functions