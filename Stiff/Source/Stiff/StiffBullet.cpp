// Fill out your copyright notice in the Description page of Project Settings.


#include "StiffBullet.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
AStiffBullet::AStiffBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SetRootComponent(Mesh);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MOVEMENT"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->bSimulationEnabled = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ST_BULLET(TEXT("/Game/Resources/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_40mm_G.SM_Shell_40mm_G"));

	if (ST_BULLET.Succeeded())
	{
		Mesh->SetStaticMesh(ST_BULLET.Object);
	}

	GetRootComponent()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));

}

// Called when the game starts or when spawned
void AStiffBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStiffBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStiffBullet::FireToDirection(const FRotator& Direction, const FRotator& BulletRotation)
{
	GetRootComponent()->SetWorldRotation(BulletRotation);
	ProjectileMovementComponent->Velocity = Direction.Vector() * ProjectileMovementComponent->InitialSpeed;
}
