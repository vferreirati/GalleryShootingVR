// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPlayer.generated.h"

UCLASS()
class GALLERYSHOOTINGVR_API AVRPlayer : public APawn
{
	GENERATED_BODY()

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
