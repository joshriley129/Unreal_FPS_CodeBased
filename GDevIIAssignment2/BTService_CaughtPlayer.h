// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CaughtPlayer.generated.h"


class AGDev2GMode;

/**
 * 
 */
UCLASS()
class GDEVIIASSIGNMENT2_API UBTService_CaughtPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	AGDev2GMode* gameModeRef;
};
