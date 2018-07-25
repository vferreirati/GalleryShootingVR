// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "VRPlayer.h"


AVRGameMode::AVRGameMode() {
	EnemiesPerWave.Add(3);
	EnemiesPerWave.Add(4);
	EnemiesPerWave.Add(5);

	DelayPerWave = 10;

	CurrentWaveNumber = 0;
}

void AVRGameMode::StartPlay() {
	Super::StartPlay();

	// Get all EnemySpawners in the world.
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawners);
	
}

void AVRGameMode::StartGame() {
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_DelayBetweenWaves)) { return; }

	if (AVRPlayer* Player = Cast<AVRPlayer>(UGameplayStatics::GetPlayerPawn(this, 0))) {
		Player->ResetScore();
		CurrentWaveNumber = 0;
		GetWorldTimerManager().SetTimer(TimerHandle_DelayBetweenWaves, this, &AVRGameMode::SpawnEnemyWave, DelayPerWave);
		OnGameStateChanged.Broadcast(true);
	}
}

void AVRGameMode::EndGame() {
	// Broadcast that the game ended (Toggle widget visibility)
	OnGameStateChanged.Broadcast(false);
}

void AVRGameMode::QuitGame() {
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("Quit");
}

void AVRGameMode::SpawnEnemyWave() {

	// If reached total number of waves, end game
	if (CurrentWaveNumber >= EnemiesPerWave.Num()) { 
		EndGame(); 
		return;
	}

	int32 EnemiesAmount = EnemiesPerWave[CurrentWaveNumber];

	for (int32 i = 0; i < EnemiesAmount; i++) {
		int32 RandomIndex = FMath::RandRange(0, EnemySpawners.Num() - 1);
		if (AEnemySpawner* Spawner = Cast<AEnemySpawner>(EnemySpawners[RandomIndex])) {
			Spawner->SpawnEnemy();
		}
	}

	CurrentWaveNumber++;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayBetweenWaves, this, &AVRGameMode::SpawnEnemyWave, DelayPerWave);
}