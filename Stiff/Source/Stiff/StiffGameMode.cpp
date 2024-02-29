// Copyright Epic Games, Inc. All Rights Reserved.

#include "StiffGameMode.h"
#include "StiffCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStiffGameMode::AStiffGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
