// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "StiffAnimInstance.h"
#include "StiffBullet.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, -5.0f, 10.0f + BaseEyeHeight));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN_Arms(TEXT("SkeletalMesh'/Game/Resources/Man/Mesh/Parts/SK_Man_Arms.SK_Man_Arms'"));
	if (SK_MAN_Arms.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAN_Arms.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> MAN_ANIM(TEXT("/Game/Resources/AnimStarterPack/ArmsAnim/ManArmsAnimBlueprint.ManArmsAnimBlueprint_C"));

	if (MAN_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MAN_ANIM.Class);
	}

	Camera->SetRelativeRotation(FRotator::ZeroRotator);
	Camera->bUsePawnControlRotation = true;
	bUseControllerRotationPitch = true;

	FName GunSocket(TEXT("gunSocket"));
	if (GetMesh()->DoesSocketExist(GunSocket))
	{
		Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GUN"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ST_GUN(TEXT("/Game/Resources/FPS_Weapon_Bundle/Weapons/Meshes/ENT_GUN/Meshes/Rifle_Static.Rifle_Static"));
		if (ST_GUN.Succeeded())
		{
			Gun->SetStaticMesh(ST_GUN.Object);
		}
		Gun->SetupAttachment(GetMesh(), GunSocket);
	}

	ProjectileClass = AStiffBullet::StaticClass();
}

void APlayableCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASAnim = Cast<UStiffAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayableCharacter::Fire);

	PlayerInputComponent->BindAxis(TEXT("ForwardBack"), this, &APlayableCharacter::ForwardBack);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &APlayableCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayableCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayableCharacter::Turn);
}

void APlayableCharacter::ForwardBack(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void APlayableCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void APlayableCharacter::Fire()
{
	ASAnim->FireOn();
	if (ProjectileClass && ASAnim->GetIsFire())
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FName BulletSocket(TEXT("BulletSocket"));
			FRotator BulletSpawnRotation;
			if (Gun->DoesSocketExist(BulletSocket))
			{
				Gun->GetSocketWorldLocationAndRotation(BulletSocket, BulletSpawnLocation, BulletSpawnRotation);
			}

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			AStiffBullet* Projectile = World->SpawnActor<AStiffBullet>(ProjectileClass, BulletSpawnLocation, FRotator::ZeroRotator, SpawnParams);
			FRotator ShootingDirection = GetControlRotation();
			FRotator BulletRotation = Gun->GetSocketQuaternion(BulletSocket).Rotator();
			Projectile->FireToDirection(ShootingDirection, BulletRotation);
		}
		else UE_LOG(LogTemp, Log, TEXT("World not exist"));
		

	}
	else UE_LOG(LogTemp, Log, TEXT("Projectile not exist"));
}

void APlayableCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void APlayableCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

