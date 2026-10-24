// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveElephant.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveElephant::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& OccupiedCells) const
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;

	// 走“田”字：两个方向都必须是 2 格，也就是标准的斜走两格
	if (FMath::Abs(DeltaX) != 2 || FMath::Abs(DeltaY) != 2)
	{
		return false;
	}

	// 塞象眼：起点到终点的正中那一格如果有棋子，就不能走
	const FVector2D EyeCell(FromX + DeltaX / 2, FromY + DeltaY / 2);
	if (UChessStaticFun::IsCellOccupied(EyeCell, OccupiedCells))
	{
		return false;
	}

	// 象/相不能过河：红方只能待在 Y < RiverY 的半场，蓝方只能待在 Y >= RiverY 的半场
	if (Camp == EChessCamp::ECT_Red && ToY >= ChessBoard::RiverY)
	{
		return false;
	}
	if (Camp == EChessCamp::ECT_Blue && ToY < ChessBoard::RiverY)
	{
		return false;
	}

	return true;
}
