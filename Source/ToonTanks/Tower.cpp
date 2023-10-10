// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay() {
    Super::BeginPlay();
    Tank = (ATank*)UGameplayStatics::GetPlayerPawn(this, 0);
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (Tank) {
        TankDist = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (TankDist <= FireDist) {
            Super::Rotate(Tank->GetActorLocation());
        }
    }

}

void ATower::CheckFireCondition() {
    if (TankDist <= FireDist) {
        ATower::Fire();
    }
}

void ATower::HandleDestruction() {
    Super::HandleDestruction();
    Destroy();
}