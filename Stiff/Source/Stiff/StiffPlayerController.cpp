// Fill out your copyright notice in the Description page of Project Settings.


#include "StiffPlayerController.h"

void AStiffPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}