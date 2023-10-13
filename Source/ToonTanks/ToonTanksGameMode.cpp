// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay() {
    Super::BeginPlay();

    StartGame();

    TargetTowers = CountTowers();
    
    Tank = (ATank*)UGameplayStatics::GetPlayerPawn(this, 0);
    TankPlayerController = (ATankPlayerController*)UGameplayStatics::GetPlayerController(this, 0);
    if (TankPlayerController) {
        TankPlayerController->SetPlayerEnabledState(false);
    }

    FTimerHandle BeginPlayTimerHandle;
    FTimerDelegate BeginPlayTimerDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &ATankPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(BeginPlayTimerHandle, BeginPlayTimerDelegate, StartDelay, false);
}

void AToonTanksGameMode::ActorDied (AActor *DeadActor) {
    if (DeadActor == Tank) {
        Tank->HandleDestruction();
        if (TankPlayerController) {
            TankPlayerController->SetPlayerEnabledState(false);
            GameOver(false);
        }
    } else if (ATower *DestroyedTower = Cast<ATower>(DeadActor)) {
        DestroyedTower->HandleDestruction();
        if (!--TargetTowers) {
            GameOver(true);
        }
    }
}

int32 AToonTanksGameMode::CountTowers() {
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}

