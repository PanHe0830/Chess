// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"


void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>();
	if (ChessManager)
	{
		
	}
}
