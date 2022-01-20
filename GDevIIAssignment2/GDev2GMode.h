// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDevIIAssignment2GameModeBase.h"
#include "GDev2GMode.generated.h"

class ASpawnPoints;
/**
 * 
 */
UCLASS()
class GDEVIIASSIGNMENT2_API AGDev2GMode : public AGDevIIAssignment2GameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;  // Start function
	void Tick(float DeltaTime);         // Update function  
	AActor* ChooseSpawnpoint();         // Function chooses a spawnpoint
	void SpawnEnemies();                // Function spawns enemies

public:
	UFUNCTION(BlueprintCallable)        // Can be called from blueprint  
		void EnemyKilled();             // Function containing what to do when an enemy is killed
	UFUNCTION()
		void CoconutHit();              // Coconut hit controller
	UFUNCTION()
		void RoundCheck();              // Checks round is over or not
	UFUNCTION(BlueprintPure)            // Can be called from blueprint  
		int GetScore();                 // Gets current score for UI
	UFUNCTION(BlueprintPure)            // Can be called from blueprint  
		int GetRound();                 // Gets current round for UI
	UFUNCTION()
		void GameOver();                // changes to game over screen
private:
	// Enmey spawn points
	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawnPoints;    // Array of spawn points

	// Enemies in play
	UPROPERTY()
		int enemies = 0;                // Number of enemies in a scene

	// Enemy class
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> enemyClass;// Enemy class (for spawning)

	// Round Count
	UPROPERTY(EditAnywhere)
		int currentRound;              // referenece to the current round 

	// Score Count
	UPROPERTY(EditAnywhere)
		int currentScore;              // referenece to the current score 

	// Mid spawning
	UPROPERTY()
		bool spawning = false;         // spawn lock checker

};
