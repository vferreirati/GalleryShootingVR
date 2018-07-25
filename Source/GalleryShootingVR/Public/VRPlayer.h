// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, int32, NewScore);

UCLASS()
class GALLERYSHOOTINGVR_API AVRPlayer : public APawn
{
	GENERATED_BODY()

public:

	FOnScoreChangedSignature OnScoreChanged;

public:
	// Sets default values for this pawn's properties
	AVRPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UMotionControllerComponent* ControllerRight;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UMotionControllerComponent* ControllerLeft;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ControllerMeshRight;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ControllerMeshLeft;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* MuzzleLocation;

	// Range in cm's of the player gun
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float GunRange;

	// Current score of the player
	int32 PlayerScore;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Does a linetrace shoot
	void Shoot();

	// Adds or subtracts to player score
	void AddToScore(int32 Value);

	// Resets the score back to 0
	void ResetScore();
};
