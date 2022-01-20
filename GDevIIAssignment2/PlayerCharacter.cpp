// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GDev2GMode.h"
#include "Gun.h"
#include "Bullet.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Gun setup
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	gunMesh->SetupAttachment(RootComponent);
	gunMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("weapon_placement"));

	// Bullet Placement setup
	bulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	bulletSpawnPoint->SetupAttachment(gunMesh);
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	gameModeRef = Cast<AGDev2GMode>(UGameplayStatics::GetGameMode(GetWorld()));  // gets a reference of the game mode
	UGameplayStatics::PlaySound2D(GetWorld(), sound1, 1.0f, 1.0f, 0.0f);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	gameModeRef->RoundCheck(); // checks if the round is still going or not
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Setting up movement bindings
	PlayerInputComponent->BindAxis(TEXT("Move Forwards"), this, &APlayerCharacter::MoveForwards);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::Fire);
}

void APlayerCharacter::Caught()
{
	gameModeRef->GameOver();
}

// Moves a character forwards or backwards
void APlayerCharacter::MoveForwards(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount /** GetWorld()->DeltaTimeSeconds*/);
	
}

// Moves a character left or right
void APlayerCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

// Controls character lookiung up or down
void APlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

// Controls a character looking left or right
void APlayerCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

// Allows a player to jump
void APlayerCharacter::Jump()
{
	// No implementation, wasnt wanted
}

// Lets a player shoot a weapon
void APlayerCharacter::Fire()
{
	// Spawn bullets !!!- Removed in later builds
	//FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
	//FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
	//ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);

	// Raycast work
	AController* controllerRef = GetController();
	FVector camLoc;
	FRotator camRot;
	controllerRef->GetPlayerViewPoint(camLoc, camRot); // get camera viewpoint
	FVector castEnd = camLoc + camRot.Vector() * castRange; // gets cast ray finish point from camera for the cast range
	UGameplayStatics::PlaySound2D(GetWorld(), gunSound, 1.0f, 1.0f, 0.0f); // play laser beam sound from gun
	FHitResult hit; // sets up hit target
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(hit, camLoc, castEnd, ECC_Visibility); // fires ray 
	if (hit.GetActor() != nullptr)
	{
		if (bDidHit) {
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *hit.GetActor()->GetName()); // if hits, output name

			float impForce = 1000; // add an impulse of 1000 to the object
			UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(hit.GetActor()->GetRootComponent());
			if (rootComp->IsSimulatingPhysics()) // checks if the object is simulating physics, error checking
			{
				rootComp->AddImpulse(camRot.Vector() * impForce * rootComp->GetMass()); // adds the impulse
				gameModeRef->CoconutHit(); // hits the coconut in game mode
			}
			UGameplayStatics::ApplyDamage(hit.GetActor(), 10.0f, GetController(), this, UDamageType::StaticClass()); // calls apply damage function to whatever is hit
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Missed")); // if missed then output that
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Hit Alien Object")); // if missed then output that
	}
}

void APlayerCharacter::GetViewpoint() // gets players viewpoint 
{
	AController* controllerRef = GetController();
	FVector camLoc;
	FRotator camRot;
	controllerRef->GetPlayerViewPoint(camLoc, camRot);
}