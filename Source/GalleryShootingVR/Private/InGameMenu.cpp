// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "VRGameMode.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"


// Sets default values
AInGameMenu::AInGameMenu()
{
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	SetRootComponent(WidgetComp);

	StartBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("StartBoxComp"));
	StartBoxComp->ComponentTags.Add("StartBox");
	StartBoxComp->SetCollisionProfileName("UI");
	StartBoxComp->SetupAttachment(GetRootComponent());

	EndBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("EndBoxComp"));
	EndBoxComp->ComponentTags.Add("QuitBox");
	EndBoxComp->SetCollisionProfileName("UI");
	EndBoxComp->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AInGameMenu::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<AVRGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnGameStateChanged.AddDynamic(this, &AInGameMenu::ToggleMenu);
}

void AInGameMenu::InteractWithMenu(class UPrimitiveComponent* HitComp) {
	if (!GameMode) {
		UE_LOG(LogTemp, Error, TEXT("INVALID GAMEMODE"))
		return;
	}

	if (HitComp->ComponentHasTag("StartBox")) {
		GameMode->StartGame();

	} else if(HitComp->ComponentHasTag("QuitBox")) {
		GameMode->QuitGame();
	}
}

void AInGameMenu::ToggleMenu(bool IsGamePlaying) {
	if (IsGamePlaying) {
		WidgetComp->SetVisibility(false);
		StartBoxComp->SetCollisionProfileName("NoCollision");
		EndBoxComp->SetCollisionProfileName("NoCollision");
	} else {
		WidgetComp->SetVisibility(true);
		StartBoxComp->SetCollisionProfileName("UI");
		EndBoxComp->SetCollisionProfileName("UI");
	}
}