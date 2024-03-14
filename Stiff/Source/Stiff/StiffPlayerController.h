// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stiff.h"
#include "GameFramework/PlayerController.h"
#include "StiffPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STIFF_API AStiffPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;
	
};
