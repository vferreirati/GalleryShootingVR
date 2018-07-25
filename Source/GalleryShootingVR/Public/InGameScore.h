// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameScore.generated.h"

UCLASS()
class GALLERYSHOOTINGVR_API AInGameScore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInGameScore();

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWidgetComponent* WidgetComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "InGameScore")
	void UpdateDisplayedScore(int32 NewScore);	
};