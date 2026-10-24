// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveCannon.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveCannon::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& OccupiedCells) const
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;

	// 炮只能沿直线走，且必须真的移动（排除原地不动）
	if (DeltaX != 0 && DeltaY != 0)
	{
		return false;
	}
	if (DeltaX == 0 && DeltaY == 0)
	{
		return false;
	}

	const int32 PiecesBetween = UChessStaticFun::CountPiecesBetween(From, To, OccupiedCells);
	const bool bTargetOccupied = UChessStaticFun::IsCellOccupied(To, OccupiedCells);

	// 不吃子（目标格为空）：中间不能有棋子，走法同车
	// 吃子（目标格有子）：中间必须正好隔一个棋子，这就是“炮翻山”
	return bTargetOccupied ? (PiecesBetween == 1) : (PiecesBetween == 0);
}
