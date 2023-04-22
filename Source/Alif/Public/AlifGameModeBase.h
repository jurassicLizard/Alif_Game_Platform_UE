// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AlifGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ALIF_API AAlifGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**Constructor*/
	AAlifGameModeBase();
	/**Constructor End*/

	/**Begin class Interface*/

	/**Init game state place holder*/

	// virtual void InitGameState() override;

	/**Handle New Player and skips pawn spawning
	 * @param NewPlayer
	*/

	virtual void RestartPlayer(AController* NewPlayer) override;


	/**Modify the damage we want to apply to an actor*/

	// virtual void ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;


	/**End class Interface*/


	/**BEGIN general game controls*/
	/**Finish the game with selected team as winner
	 * @param InWinningTeam the team that has won
	*/
	void FinishGame(FString CurrentlyNOTIMPLEMENTED);

	/**Return to menu function*/

	void ReturnToMenu();

	/**Exit Game helper*/

	void ExitGame();

	/**End general game controls*/



	/**Helper Function to test teams (null = not in friendly team)
	 * 
	 * @param ActorToTestAgainst
	 * @param ActorBeingTested
	 * 
	 * @returns true if the actors are on the same team, false otherwise
	*/

	bool IsOnFriendlyTeam(const AActor* ActorToTestAgainst, const AActor* ActorBeingTested);

private:

	FTimerHandle ReturnToMenuTimer;

	





	


	
};
