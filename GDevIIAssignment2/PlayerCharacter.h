// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class ABullet;
class AGDev2GMode;

UCLASS()
class GDEVIIASSIGNMENT2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Caught();
	
private:
	// Bullet Class
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> bulletClass;

	// Gun Skeletal Mesh
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* gunMesh;
	
	// Bullet Spawn Point
	UPROPERTY(EditAnywhere)
		USceneComponent* bulletSpawnPoint;

	// RayCast Range
	UPROPERTY(EditAnywhere)
		float castRange;

	// Game mode reference
	UPROPERTY(EditAnywhere)
		AGDev2GMode* gameModeRef;

	// Game mode reference
	UPROPERTY(EditAnywhere)
		USoundBase* sound1;
	UPROPERTY(EditAnywhere)
		USoundBase* gunSound;

	// Movement Functions
	void MoveForwards(float AxisAmount);
	void Strafe(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);

	// Action Functions
	void Jump();
	void Fire();

	// Raycast Functions
	void GetViewpoint();
};
