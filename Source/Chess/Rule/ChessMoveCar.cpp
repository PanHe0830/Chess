// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveCar.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveCar::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells) const
{
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));
	const bool bStraight = (DeltaX == 0) != (DeltaY == 0);
	if (!bStraight)
	{
		return false;
	}

	return !UChessStaticFun::HasPieceOnPath(From, To, OccupiedCells);
}
