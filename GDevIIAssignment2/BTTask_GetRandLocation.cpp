// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandLocation.h"
#include "AIControl.h"
#include "NavigationSystem.h"
#include "behaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetRandLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory); // Call the super as this is an override

	if (OwnerComp.GetAIOwner() == nullptr) { // check if ownercomp.aiowner is not null
		return EBTNodeResult::Failed;
	}
	AActor* aiActor = OwnerComp.GetAIOwner()->GetPawn(); // get the pawn

	float randomRadius = 2000.0f; // random range reach
	FNavLocation randLoc;

	UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	navSys->GetRandomReachablePointInRadius(aiActor->GetActorLocation(), randomRadius, randLoc); // Gets random location within reach

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"), randLoc); // sets position in blackboard 

	return EBTNodeResult::Succeeded;
}