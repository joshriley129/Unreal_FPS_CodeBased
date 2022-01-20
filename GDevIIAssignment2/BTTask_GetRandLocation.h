// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandLocation.generated.h"

/**
 * 
 */
UCLASS()
class GDEVIIASSIGNMENT2_API UBTTask_GetRandLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
