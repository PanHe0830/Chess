// Fill out your copyright notice in the Description page of Project Settings.


#include "UChessStaticFun.h"

void UChessStaticFun::PrintStringMessage(FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
}

bool UChessStaticFun::IsStraightLine(const FVector2D& From, const FVector2D& To)
{
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));
	return (DeltaY + DeltaX) == 1 ? true : false;
}

bool UChessStaticFun::HasPieceOnPath(const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells)
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);
	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;
	if ((DeltaX != 0 && DeltaY != 0) || (DeltaX == 0 && DeltaY == 0))
	{
		return false;
	}

	const int32 StepX = FMath::Sign(DeltaX);
	const int32 StepY = FMath::Sign(DeltaY);
	for (int32 X = FromX + StepX, Y = FromY + StepY; X != ToX || Y != ToY; X += StepX, Y += StepY)
	{
		const bool bOccupied = OccupiedCells.ContainsByPredicate([X, Y](const FVector2D& Cell)
		{
			return FMath::RoundToInt(Cell.X) == X && FMath::RoundToInt(Cell.Y) == Y;
		});
		if (bOccupied)
		{
			return true;
		}
	}

	return false;
}
