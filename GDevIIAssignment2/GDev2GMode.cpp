// Fill out your copyright notice in the Description page of Project Settings.


#include "GDev2GMode.h"
#include "SpawnPoints.h"
#include "Kismet/GameplayStatics.h"

void AGDev2GMode::BeginPlay()   // Spawns original enemies
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoints::StaticClass(), spawnPoints);   // Adds spawn points to an array

	SpawnEnemies(); // spawns enemies
	
}

void AGDev2GMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    // does nothing
}

AActor* AGDev2GMode::ChooseSpawnpoint()    // Chooses spawnpoints
{
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);
	return spawnPoints[index]; // returns an actor
}

void AGDev2GMode::SpawnEnemies()
{
	for (int i = 0; i < currentRound * 5; ++i)
	{
		AActor* spwnPnt = ChooseSpawnpoint();  // gets a random spawn point
		FVector spawnLocation = spwnPnt->GetActorLocation(); // gets location and rotation
		FRotator spawnRotation = spwnPnt->GetActorRotation();
		AActor* TempEnemy = GetWorld()->SpawnActor<AActor>(enemyClass, spawnLocation, spawnRotation); // spawns actor
		enemies++; // increases enemy count

		UE_LOG(LogTemp, Warning, TEXT("The enemy count value is: %d"), enemies); // outputs enemy count
	}
	spawning = false; // unlocks spawn lock
}

void AGDev2GMode::EnemyKilled()
{
	enemies--; // reduce enemy count
	UE_LOG(LogTemp, Warning, TEXT("Point++")); // add points
	UE_LOG(LogTemp, Warning, TEXT("The enemy count value is: %d"), enemies);
}

void AGDev2GMode::CoconutHit() // add pointys when hit coconut
{
	UE_LOG(LogTemp, Warning, TEXT("Point++"));
	currentScore++;
}

void AGDev2GMode::RoundCheck() // chechks the current round is still going
{
	if (enemies <= 0) // if still enemies
	{			
		if (spawning != true) // if not spawn locked
		{
			currentRound++; // increase round
			currentScore+= 10;
			FTimerHandle NextRoundTimer; // start countdown timer
			GetWorld()->GetTimerManager().SetTimer(NextRoundTimer, this, &AGDev2GMode::SpawnEnemies, 5.0f, false); // spawn enemies after 5 seconds
			spawning = true; // lock 
		}
		spawning = true; // double lock (just in case)
	}
}

int AGDev2GMode::GetScore()
{
	return currentScore;
}

int AGDev2GMode::GetRound()
{
	return currentRound;
}

void AGDev2GMode::GameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), "End");
}
