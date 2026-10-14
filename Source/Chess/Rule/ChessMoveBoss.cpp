// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveBoss.h"

bool UChessMoveBoss::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To) const
{
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));
	if (DeltaX + DeltaY != 1)
	{
		return false;
	}
	const int32 X = FMath::RoundToInt(To.X);
	const int32 Y = FMath::RoundToInt(To.Y);
	const bool bInsidePalace = X >= 3 && X <= 5
		&& (Camp == EChessCamp::ECT_Red ? (Y >= 0 && Y <= 2) : (Y >= 7 && Y <= 9));
	return bInsidePalace;
}
