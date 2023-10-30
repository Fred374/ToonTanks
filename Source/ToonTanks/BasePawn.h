// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePawn")
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePawn")
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePawn")
	UStaticMeshComponent *TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePawn")
	USceneComponent *ProjSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "BasePawn")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "BasePawn")
	class UParticleSystem *DeathParticles;

	UPROPERTY(EditAnywhere, Category = "BasePawn")
	class USoundBase *DeathSound;

	UPROPERTY(EditAnywhere, Category = "BasePawn")
	TSubclassOf<class UCameraShakeBase> DeathShakeClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	void Rotate(FVector LookAtTarget);

	void Fire();

};
