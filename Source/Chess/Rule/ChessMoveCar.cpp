// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveCar.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveCar::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& OccupiedCells) const
{
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));

	// 车只能沿横线或竖线走：恰好一个方向有位移。
	// 用 != 当 XOR 用，同时排除原地不动（两个方向都没有位移）的情况。
	const bool bStraight = (DeltaX == 0) != (DeltaY == 0);
	if (!bStraight)
	{
		return false;
	}

	// 路径上不能有任何棋子挡着
	return !UChessStaticFun::HasPieceOnPath(From, To, OccupiedCells);
}
