// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveHorse.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveHorse::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& OccupiedCells) const
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;

	const int32 AbsX = FMath::Abs(DeltaX);
	const int32 AbsY = FMath::Abs(DeltaY);

	// 走“日”字：一个方向 2 格、另一个方向 1 格
	if (!((AbsX == 2 && AbsY == 1) || (AbsX == 1 && AbsY == 2)))
	{
		return false;
	}

	// 马腿：沿“2 格”那个方向的相邻格如果被占，就是蹩马腿，不能走。
	// 例如横着走 2 格时，被挡的是 (FromX + Sign(DeltaX), FromY) 这一格。
	const FVector2D LegCell = (AbsX == 2)
		? FVector2D(FromX + FMath::Sign(DeltaX), FromY)
		: FVector2D(FromX, FromY + FMath::Sign(DeltaY));

	return !UChessStaticFun::IsCellOccupied(LegCell, OccupiedCells);
}
