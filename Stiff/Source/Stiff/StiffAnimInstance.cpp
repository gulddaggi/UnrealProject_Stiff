// Fill out your copyright notice in the Description page of Project Settings.


#include "StiffAnimInstance.h"

UStiffAnimInstance::UStiffAnimInstance()
{
	CurrentSpeed = 0.0f;
}

void UStiffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		CurrentSpeed = Pawn->GetVelocity().Size();
	}
}

