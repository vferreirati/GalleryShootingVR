// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayer.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"


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

}

