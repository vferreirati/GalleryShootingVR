// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VRGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GALLERYSHOOTINGVR_API AVRGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AVRGameMode();

	virtual void StartPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<int32> EnemiesPerWave;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DelayPerWave;

	int32 CurrentWaveNumber;

	TArray<AActor*> EnemySpawners;

	FTimerHandle TimerHandle_DelayBetweenWaves;

protected:
	void SpawnEnemyWave();
};
