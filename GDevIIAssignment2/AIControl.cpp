// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControl.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h" 
#include "BehaviorTree/BlackboardComponent.h"

void AAIControl::BeginPlay() {
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), waypoints); // combines all waypoints into one array
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // gets refernce to player pawn
	if (enemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(enemyBehaviorTree); // starts behaviour tree
	}
	GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPoint"), ChooseWaypoint()->GetActorLocation()); // sets first two waypoints
	GetBlackboardComponent()->SetValueAsVector(TEXT("Targetpoint2"), ChooseWaypoint()->GetActorLocation());


}

void AAIControl::Tick(float DeltaTime) // update function
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // gets refernce to player pawn
	
	//GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPoint"), ChooseWaypoint()->GetActorLocation()); // changes waypoiunts each frame so will alwway have different targets
	//GetBlackboardComponent()->SetValueAsVector(TEXT("Targetpoint2"), ChooseWaypoint()->GetActorLocation());

	if (LineOfSightTo(PlayerPawn)) // Updates when player is in line of sight
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation()); // sets players location
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

AActor* AAIControl::ChooseWaypoint() // chooses random waypoint
{
	int index = FMath::RandRange(0, waypoints.Num() - 1);
	return waypoints[index]; 
}

void AAIControl::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) // when reached waypoint (changed by behaviour tree)
{
	Super::OnMoveCompleted(RequestID, Result);
	/*RandomPatrol();*/
}

void AAIControl::RandomPatrol() // moves to waypoint (replaced by behaviour tree)
{
	MoveToActor(ChooseWaypoint()); // moves to the waypoint
}
