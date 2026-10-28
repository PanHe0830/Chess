// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveBoss.h"

bool UChessMoveBoss::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& /*OccupiedCells*/) const
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = FMath::Abs(ToX - FromX);
	const int32 DeltaY = FMath::Abs(ToY - FromY);

	// 帅/将每次只能沿横线或竖线走一步：两个方向上的位移加起来必须是 1
	//if (DeltaX + DeltaY != 1)
	//{
	//	return false;
	//}

	// 只能在九宫内活动
	const bool bInsidePalaceY = ToY >= ChessBoard::PalaceMinY && ToY <= ChessBoard::PalaceMaxY;
	const bool bInsidePalaceX = (Camp == EChessCamp::ECT_Red)
		? (ToX >= ChessBoard::RedPalaceMinX && ToX <= ChessBoard::RedPalaceMaxY)
		: (ToX >= ChessBoard::BluePalaceMinX && ToX <= ChessBoard::BluePalaceMaxY);

	return bInsidePalaceX && bInsidePalaceY;
}