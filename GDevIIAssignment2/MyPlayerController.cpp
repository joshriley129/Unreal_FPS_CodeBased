// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()  // Begin play adds the crosshair to the screen
{
	Super::BeginPlay();

	crosshairUI = CreateWidget(this, crosshairClass);  //Adds crosshair to screen

	if (crosshairUI != nullptr) {
		crosshairUI->AddToViewport(); // checks crosshair is assigned
	}
}