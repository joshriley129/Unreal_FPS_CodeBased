// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GameOver.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GDev2GMode.h"

EBTNodeResult::Type UBTTask_GameOver::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory); // Call the super as this is an override

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // gets refernce to player pawn
	AAIController* enemyAIController = OwnerComp.GetAIOwner(); // Return ai controller


	UGameplayStatics::ApplyDamage(PlayerPawn, 10.0f, OwnerComp.GetAIOwner(), enemyAIController, UDamageType::StaticClass()); // calls apply damage function to whatever is hit

	return EBTNodeResult::Succeeded;
}