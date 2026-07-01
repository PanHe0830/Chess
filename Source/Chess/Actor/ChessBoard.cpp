// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"

AChessBoard::AChessBoard()
{
	PrimaryActorTick.bCanEverTick = true;
	BoardPoint = FVector2D(0,0);
}

void AChessBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessBoard::SetBoardPoint(FVector2D point)
{
	BoardPoint = point;
}

FVector2D AChessBoard::GetBoardPoint() const
{
	return BoardPoint;
}

void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

