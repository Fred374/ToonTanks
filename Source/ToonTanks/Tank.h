// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:

		ATank();

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		void HandleDestruction();

		APlayerController *GetTankPlayerController() const {return TankPlayerController;}

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:

		UPROPERTY(VisibleAnywhere, Category = "Tank")
		class UCameraComponent *CameraComp;
	
		UPROPERTY(VisibleAnywhere, Category = "Tank")
		class USpringArmComponent *SpringArmComp;

		APlayerController *TankPlayerController;

		UPROPERTY(EditAnywhere, Category = "Tank")
		float Speed = 300.0f;
		
		UPROPERTY(EditAnywhere, Category = "Tank")
		float TurnRate = 45.0f;

		void Move(float Value);

		void Rotate(float Value);

		void Turn(float Value);
};
