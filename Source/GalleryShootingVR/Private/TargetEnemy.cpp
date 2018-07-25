// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetEnemy.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATargetEnemy::ATargetEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
}

// Called when the game starts or when spawned
void ATargetEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

