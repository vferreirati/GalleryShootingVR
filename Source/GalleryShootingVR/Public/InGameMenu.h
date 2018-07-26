// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameMenu.generated.h"

UCLASS()
class GALLERYSHOOTINGVR_API AInGameMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInGameMenu();

	void InteractWithMenu(class UPrimitiveComponent* HitComp);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* StartBoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* EndBoxComp;

	class AVRGameMode* GameMode;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameMenu")
	void ToggleMenu(bool IsGamePlaying);
};
