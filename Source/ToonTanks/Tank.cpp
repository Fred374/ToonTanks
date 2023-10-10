// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() {
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAxis(("RotateTurret"), this, &ATank::Rotate);
    PlayerInputComponent->BindAction(("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	TankPlayerController = (APlayerController*)GetController();
}

void ATank::Move(float Value) {
    float DeltaSpeed = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation = FVector(DeltaSpeed, 0, 0);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Rotate(float Value) {
    FHitResult HitResult;
    if (TankPlayerController) {
        TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        Super::Rotate(HitResult.ImpactPoint);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 1, FColor::Red);
    }
}

void ATank::Turn(float Value) {
    float DeltaRate = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotator = FRotator(0, DeltaRate, 0);
    AddActorLocalRotation(DeltaRotator, true);
}

void ATank::HandleDestruction() {
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}