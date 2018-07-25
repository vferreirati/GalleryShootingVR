// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Components/BillboardComponent.h"
#include "Engine/World.h"
#include "TargetEnemy.h"
#include "TimerManager.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComp"));
	SetRootComponent(BillboardComp);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::SpawnEnemy() {
	if (TargetEnemyClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ATargetEnemy>(TargetEnemyClass, GetTransform(), SpawnParams);
	}
}