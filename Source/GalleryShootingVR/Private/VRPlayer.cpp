// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayer.h"
#include "TargetEnemy.h"
#include "InGameMenu.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVRPlayer::AVRPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(VRRoot);

	ControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("ControllerRight"));
	ControllerRight->SetTrackingSource(EControllerHand::Right);
	ControllerRight->SetupAttachment(VRRoot);

	ControllerMeshRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControllerMeshRight"));
	ControllerMeshRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ControllerMeshRight->SetupAttachment(ControllerRight);

	ControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("ControllerLeft"));
	ControllerLeft->SetTrackingSource(EControllerHand::Left);
	ControllerLeft->SetupAttachment(VRRoot);

	ControllerMeshLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControllerMeshLeft"));
	ControllerMeshLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ControllerMeshLeft->SetupAttachment(ControllerLeft);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(ControllerMeshRight);

	GunRange = 1500;	// 1.5 Meters
	PlayerScore = 0;
}

// Called when the game starts or when spawned
void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

// Called every frame
void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AVRPlayer::Shoot);
}

void AVRPlayer::Shoot() {
	FVector StartLocation = MuzzleLocation->GetComponentLocation();
	FVector EndLocation = StartLocation + (MuzzleLocation->GetComponentRotation().Vector() * GunRange);
	FHitResult HitResult;
	bool bLineTraceHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	if (bLineTraceHit) {
		PlayHitEffect(HitResult.ImpactPoint);
		
		if (ATargetEnemy* Enemy = Cast<ATargetEnemy>(HitResult.Actor)) {
			Enemy->WasHit();
			AddToScore(5);
		
		} else if(AInGameMenu* Menu = Cast<AInGameMenu>(HitResult.Actor)) {
			Menu->InteractWithMenu(HitResult.GetComponent());
		}

		
	}
}

void AVRPlayer::PlayHitEffect(FVector Location) {
	if (HitEffect) {
		UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Location);
	}
}

void AVRPlayer::AddToScore(int32 Value) {
	PlayerScore += Value;
	OnScoreChanged.Broadcast(PlayerScore);	// Broadcast the event that our score changed
}

void AVRPlayer::ResetScore() {
	PlayerScore = 0;
	OnScoreChanged.Broadcast(PlayerScore);	// Broadcast the event that our score changed
}