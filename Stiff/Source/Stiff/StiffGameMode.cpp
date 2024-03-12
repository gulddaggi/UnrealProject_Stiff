// Copyright Epic Games, Inc. All Rights Reserved.

#include "StiffGameMode.h"
#include "StiffPlayerController.h"
#include "PlayableCharacter.h"

AStiffGameMode::AStiffGameMode()
{
	DefaultPawnClass = APlayableCharacter::StaticClass();
	PlayerControllerClass = AStiffPlayerController::StaticClass();
}
