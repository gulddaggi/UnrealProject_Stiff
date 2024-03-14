// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stiff.h"
#include "Animation/AnimInstance.h"
#include "StiffAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STIFF_API UStiffAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UStiffAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentSpeed;
	
};
