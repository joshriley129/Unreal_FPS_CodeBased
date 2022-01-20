// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControl.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class GDEVIIASSIGNMENT2_API AAIControl : public AAIController
{
	GENERATED_BODY()
	
public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override; // called when move completed

protected:
	virtual void BeginPlay() override; // start function
	void Tick(float DeltaTime); // update function
	AActor* ChooseWaypoint(); // chooses a waypoint from a list 
	void RandomPatrol(); // chooses a random point

private:
	UPROPERTY()
		TArray<AActor*> waypoints; // array of waypoints

	UPROPERTY(EditAnywhere)
		UBehaviorTree* enemyBehaviorTree; // reference to the behaviour tree
};
