// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GALLERYSHOOTINGVR_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Spawns a TargetEnemy
	void SpawnEnemy();

protected:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBillboardComponent* BillboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class ATargetEnemy> TargetEnemyClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
