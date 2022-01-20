// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerPosition.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_PlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds); // Calls original tick function

	AAIController* enemyAIController = OwnerComp.GetAIOwner(); // Return ai controller
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player pawn

	if (playerPawn != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerPawn->GetActorLocation());
	}
}