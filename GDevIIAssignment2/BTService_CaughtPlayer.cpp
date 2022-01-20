// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CaughtPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GDev2GMode.h"

void UBTService_CaughtPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds); // Calls original tick function

	gameModeRef = Cast<AGDev2GMode>(UGameplayStatics::GetGameMode(GetWorld()));  // gets a reference of the game mode
	gameModeRef->GameOver();
}