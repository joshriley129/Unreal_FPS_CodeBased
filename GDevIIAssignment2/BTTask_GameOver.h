// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GameOver.generated.h"


class AGDev2GMode;
/**
 * 
 */
UCLASS()
class GDEVIIASSIGNMENT2_API UBTTask_GameOver : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	AGDev2GMode* gameModeRef;

};
