// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"


// Sets default values
ATargetEnemy::ATargetEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->ProjectileGravityScale = 0;
	ProjectileComp->MaxSpeed = 5000;

	MinInitialSpeed = 200;
	MaxInitialSpeed = 350;
}

// Called when the game starts or when spawned
void ATargetEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(15);
}

// Called every frame
void ATargetEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetEnemy::WasHit() {
	Destroy();
}