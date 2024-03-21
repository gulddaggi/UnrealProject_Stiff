// Fill out your copyright notice in the Description page of Project Settings.


#include "StiffAnimInstance.h"

UStiffAnimInstance::UStiffAnimInstance()
{
	CurrentSpeed = 0.0f;
	IsFire = false;
}

void UStiffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		CurrentSpeed = Pawn->GetVelocity().Size();
	}

	if (this->GetCurrentStateName(0) == FName(TEXT("Fire")))
	{
		IsFire = false;
	}
}

void UStiffAnimInstance::FireOn()
{
	IsFire = true;
}

