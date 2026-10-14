// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveCar.h"

bool UChessMoveCar::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To) const
{
	// 车走直线 , 如果X和Y都不是0证明没走直线
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));
	
	if (DeltaX != 0 && DeltaY != 0)
	{
		return false;
	}
	
	return true;;
}
