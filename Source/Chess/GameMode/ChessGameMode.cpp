// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"


void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>();
	if (ChessManager)
	{
		FVector PositionRed = FVector::ZeroVector;
		FRotator RotationRed = FRotator::ZeroRotator;
		//ChessManager->SpawnChessBoard(PositionRed,RotationRed,100);
		//ChessManager->SpawnChessPoint(PositionRed,100);
		//
		//FVector PositionBlue = FVector::ZeroVector - FVector(100,0,0);
		//FRotator RotationBlue = FRotator::ZeroRotator;
		//ChessManager->SpawnChessBoard(PositionBlue,RotationBlue,-100);
	}
}
