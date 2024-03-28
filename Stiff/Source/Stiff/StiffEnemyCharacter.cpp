// Fill out your copyright notice in the Description page of Project Settings.


#include "StiffEnemyCharacter.h"

// Sets default values
AStiffEnemyCharacter::AStiffEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN(TEXT("/Game/Resources/Man/Mesh/Full/SK_Man_Full_04.SK_Man_Full_04"));

	if (SK_MAN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAN.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(TEXT("/Game/Resources/AnimStarterPack/ManAnimBlueprint.ManAnimBlueprint_C"));

	if (ENEMY_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);
	}


}

// Called when the game starts or when spawned
void AStiffEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStiffEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStiffEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

