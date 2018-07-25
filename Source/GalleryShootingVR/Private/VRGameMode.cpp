// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"


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
	
	GetWorldTimerManager().SetTimer(TimerHandle_DelayBetweenWaves, this, &AVRGameMode::SpawnEnemyWave, DelayPerWave);
}

void AVRGameMode::SpawnEnemyWave() {

	if (CurrentWaveNumber >= EnemiesPerWave.Num()) { return; }

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