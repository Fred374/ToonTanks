// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjSpawnPoint->SetupAttachment(TurretMesh);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::Rotate(FVector LookAtTarget) {
    FVector TurretLocation = TurretMesh->GetComponentLocation();
    FVector ToTarget = LookAtTarget - TurretLocation;
    FRotator ToTargetRot = FRotator(0, ToTarget.Rotation().Yaw, 0);
    TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
	 ToTargetRot, UGameplayStatics::GetWorldDeltaSeconds(this), 10));
}

void ABasePawn::Fire() {
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	 ProjSpawnPoint->GetComponentLocation(), ProjSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction() {
	
}