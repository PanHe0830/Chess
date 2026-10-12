// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessHUD.h"

#include "MainWidget.h"
#include "Blueprint/UserWidget.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"

void AChessHUD::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeGameMainWidget();
}

void AChessHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AChessHUD::InitializeGameMainWidget()
{
	UChessManagerSubsystem* Manager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>();
	UWorld* World = GetWorld();
	if (Manager && World)
	{
		UMainWidget* Widget = Cast<UMainWidget>(Manager->GetWidgetByName("WBP_MainWidget"));
		if (!Widget) return;
		Widget->InitializeWidget();
		Widget->AddToViewport();
	}
}
