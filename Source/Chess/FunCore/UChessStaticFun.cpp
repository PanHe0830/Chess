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
	return (DeltaY + DeltaX) == 1;
}

bool UChessStaticFun::IsSameCell(const FVector2D& A, const FVector2D& B)
{
	return FMath::RoundToInt(A.X) == FMath::RoundToInt(B.X)
		&& FMath::RoundToInt(A.Y) == FMath::RoundToInt(B.Y);
}

bool UChessStaticFun::IsCellOccupied(const FVector2D& Cell, const TArray<FVector2D>& OccupiedCells)
{
	return OccupiedCells.ContainsByPredicate([&Cell](const FVector2D& Other)
	{
		return IsSameCell(Cell, Other);
	});
}

int32 UChessStaticFun::CountPiecesBetween(const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells)
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	// 只支持同行/同列；调用方应先自己判断是直线，这里返回 -1 作为“用错了”的信号
	if (FromX != ToX && FromY != ToY)
	{
		return -1;
	}

	const int32 StepX = FMath::Sign(ToX - FromX);
	const int32 StepY = FMath::Sign(ToY - FromY);

	int32 Count = 0;
	for (int32 X = FromX + StepX, Y = FromY + StepY; X != ToX || Y != ToY; X += StepX, Y += StepY)
	{
		if (IsCellOccupied(FVector2D(X, Y), OccupiedCells))
		{
			++Count;
		}
	}

	return Count;
}

bool UChessStaticFun::HasPieceOnPath(const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells)
{
	// 复用 CountPiecesBetween：中间只要有一枚棋子就算被挡住。
	// 斜线时 CountPiecesBetween 返回 -1，同样不会大于 0，行为与原来的实现一致。
	return CountPiecesBetween(From, To, OccupiedCells) > 0;
}

bool UChessStaticFun::IsPawnMove(EChessCamp Camp, const FVector2D& From, const FVector2D& To)
{
	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;

	// 红方向 Y 增大的方向前进，蓝方向 Y 减小的方向前进
	const int32 Forward = (Camp == EChessCamp::ECT_Red) ? 1 : -1;
	if (DeltaX == 0 && DeltaY == Forward)
	{
		return true;
	}

	// 过河之后才允许左右横走一步
	const bool bCrossedRiver = (Camp == EChessCamp::ECT_Red)
		? (FromY >= ChessBoard::RiverY)
		: (FromY < ChessBoard::RiverY);

	return bCrossedRiver && FMath::Abs(DeltaX) == 1 && DeltaY == 0;
}
