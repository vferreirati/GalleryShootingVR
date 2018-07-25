// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameScore.h"
#include "VRPlayer.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInGameScore::AInGameScore()
{
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	SetRootComponent(WidgetComp);
}

// Called when the game starts or when spawned
void AInGameScore::BeginPlay()
{
	Super::BeginPlay();

	// Subscribe to OnScoreChanged event of the player
	if (AVRPlayer* Pawn = Cast<AVRPlayer>(UGameplayStatics::GetPlayerPawn(this, 0))) {
		Pawn->OnScoreChanged.AddDynamic(this, &AInGameScore::UpdateDisplayedScore);
	}
}