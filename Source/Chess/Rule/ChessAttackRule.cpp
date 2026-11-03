// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttackRule.h"

#include "Chess/Chess.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"

void UChessAttackRule::CollectTargets(AChessPoint* CurrentActor,AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	EChessType Type = CurrentActor->GetChessType();
	switch (Type)
	{
	case EChessType::ECT_Boss:
		CollectBossTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Soldier:
		CollectSoldierTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Elephant:
		CollectElephantTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Horse:
		CollectHorseTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Car:
		CollectCarTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Cannon:
		CollectCannonTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Obiit:
		CollectObiitTargets(CurrentActor, Board,OutTargets);
		break;
	default:
		break;
	}
}

void UChessAttackRule::CollectCarTargets(AChessPoint* CurrentActor, AChessGameMode* Board, TArray<AChessPoint*>& OutTargets) const
{
	if (!CurrentActor || !Board)
	{
		return;
	}

	const EChessCamp Camp = CurrentActor->GetChessCamp();
	const FVector2D From = CurrentActor->GetLastBoardPoint();
	const FVector2D To = CurrentActor->GetBoardPoint();

	const int32 FromX = FMath::RoundToInt(From.X);
	const int32 FromY = FMath::RoundToInt(From.Y);
	const int32 ToX = FMath::RoundToInt(To.X);
	const int32 ToY = FMath::RoundToInt(To.Y);

	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;

	// 车必须沿横/竖移动才有攻击朝向；原地或斜向则不寻敌
	const bool bStraight = (DeltaX == 0) != (DeltaY == 0);
	if (!bStraight)
	{
		return;
	}

	const int32 DirX = FMath::Sign(DeltaX);
	const int32 DirY = FMath::Sign(DeltaY);
	constexpr int32 MaxRange = 10;

	AChessPoint* FirstPiece = nullptr;
	int32 BestDistance = MaxRange + 1;

	const TMap<FVector2D, TObjectPtr<AChessPoint>> Occupied = Board->GetOccupiedPoints();
	for (const TPair<FVector2D, TObjectPtr<AChessPoint>>& Pair : Occupied)
	{
		AChessPoint* Other = Pair.Value.Get();
		if (!IsValid(Other) || Other == CurrentActor)
		{
			continue;
		}

		const int32 OtherX = FMath::RoundToInt(Pair.Key.X);
		const int32 OtherY = FMath::RoundToInt(Pair.Key.Y);
		const int32 OffsetX = OtherX - ToX;
		const int32 OffsetY = OtherY - ToY;

		int32 Distance = 0;
		if (DirX != 0)
		{
			if (OffsetY != 0 || FMath::Sign(OffsetX) != DirX)
			{
				continue;
			}
			Distance = FMath::Abs(OffsetX);
		}
		else
		{
			if (OffsetX != 0 || FMath::Sign(OffsetY) != DirY)
			{
				continue;
			}
			Distance = FMath::Abs(OffsetY);
		}

		if (Distance < 1 || Distance > MaxRange || Distance >= BestDistance)
		{
			continue;
		}

		BestDistance = Distance;
		FirstPiece = Other;
	}

	if (FirstPiece && FirstPiece->GetChessCamp() != Camp)
	{
		OutTargets.Add(FirstPiece);
	}
}

void UChessAttackRule::CollectBossTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
}

namespace
{
	AChessPoint* FindPieceAtCell(AChessGameMode* Board, int32 X, int32 Y)
	{
		if (!Board)
		{
			return nullptr;
		}

		for (const TPair<FVector2D, TObjectPtr<AChessPoint>>& Pair : Board->GetOccupiedPoints())
		{
			if (FMath::RoundToInt(Pair.Key.X) == X && FMath::RoundToInt(Pair.Key.Y) == Y)
			{
				return Pair.Value.Get();
			}
		}
		return nullptr;
	}

	void CollectPawnForwardTarget(AChessPoint* CurrentActor, AChessGameMode* Board, TArray<AChessPoint*>& OutTargets)
	{
		if (!CurrentActor || !Board)
		{
			return;
		}

		const int32 X = FMath::RoundToInt(CurrentActor->GetBoardPoint().X);
		const int32 Y = FMath::RoundToInt(CurrentActor->GetBoardPoint().Y);
		const int32 Forward = (CurrentActor->GetChessCamp() == EChessCamp::ECT_Red) ? 1 : -1;
		const int32 FrontY = Y + Forward;
		if (!ChessBoard::IsInside(X, FrontY))
		{
			return;
		}

		AChessPoint* Other = FindPieceAtCell(Board, X, FrontY);
		if (IsValid(Other) && Other->GetChessCamp() != CurrentActor->GetChessCamp())
		{
			OutTargets.Add(Other);
		}
	}
}

void UChessAttackRule::CollectCannonTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	if (!CurrentActor || !Board)
	{
		return;
	}

	const int32 FromX = FMath::RoundToInt(CurrentActor->GetLastBoardPoint().X);
	const int32 FromY = FMath::RoundToInt(CurrentActor->GetLastBoardPoint().Y);
	const int32 ToX = FMath::RoundToInt(CurrentActor->GetBoardPoint().X);
	const int32 ToY = FMath::RoundToInt(CurrentActor->GetBoardPoint().Y);
	const int32 DeltaX = ToX - FromX;
	const int32 DeltaY = ToY - FromY;
	const bool bStraight = (DeltaX == 0) != (DeltaY == 0);
	if (!bStraight)
	{
		return;
	}

	const int32 DirX = FMath::Sign(DeltaX);
	const int32 DirY = FMath::Sign(DeltaY);
	const EChessCamp Camp = CurrentActor->GetChessCamp();

	struct FCannonPiece
	{
		int32 Distance = 0;
		AChessPoint* Piece = nullptr;
	};
	TArray<FCannonPiece> Ahead;

	for (const TPair<FVector2D, TObjectPtr<AChessPoint>>& Pair : Board->GetOccupiedPoints())
	{
		AChessPoint* Other = Pair.Value.Get();
		if (!IsValid(Other) || Other == CurrentActor)
		{
			continue;
		}

		const int32 OffsetX = FMath::RoundToInt(Pair.Key.X) - ToX;
		const int32 OffsetY = FMath::RoundToInt(Pair.Key.Y) - ToY;
		int32 Distance = 0;
		if (DirX != 0)
		{
			if (OffsetY != 0 || FMath::Sign(OffsetX) != DirX)
			{
				continue;
			}
			Distance = FMath::Abs(OffsetX);
		}
		else
		{
			if (OffsetX != 0 || FMath::Sign(OffsetY) != DirY)
			{
				continue;
			}
			Distance = FMath::Abs(OffsetY);
		}

		if (Distance < 1)
		{
			continue;
		}
		Ahead.Add({Distance, Other});
	}

	Ahead.Sort([](const FCannonPiece& A, const FCannonPiece& B)
	{
		return A.Distance < B.Distance;
	});

	if (Ahead.Num() >= 2 && Ahead[1].Piece->GetChessCamp() != Camp)
	{
		OutTargets.Add(Ahead[1].Piece);
	}
}

void UChessAttackRule::CollectElephantTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	if (!CurrentActor || !Board)
	{
		return;
	}

	const EChessCamp Camp = CurrentActor->GetChessCamp();
	const int32 FromX = FMath::RoundToInt(CurrentActor->GetBoardPoint().X);
	const int32 FromY = FMath::RoundToInt(CurrentActor->GetBoardPoint().Y);
	constexpr int32 FlightDistance = 3;
	constexpr int32 BlastRadius = 1;
	const int32 Forward = (Camp == EChessCamp::ECT_Red) ? 1 : -1;

	const int32 ImpactX = FromX;
	const int32 ImpactY = FMath::Clamp(FromY + Forward * FlightDistance, 0, ChessBoard::Rows - 1);

	const TMap<FVector2D, TObjectPtr<AChessPoint>> Occupied = Board->GetOccupiedPoints();
	for (const TPair<FVector2D, TObjectPtr<AChessPoint>>& Pair : Occupied)
	{
		AChessPoint* Other = Pair.Value.Get();
		if (!IsValid(Other) || Other == CurrentActor || Other->GetChessCamp() == Camp)
		{
			continue;
		}

		const int32 OtherX = FMath::RoundToInt(Pair.Key.X);
		const int32 OtherY = FMath::RoundToInt(Pair.Key.Y);
		const int32 OffsetX = FMath::Abs(OtherX - ImpactX);
		const int32 OffsetY = FMath::Abs(OtherY - ImpactY);
		if (FMath::Max(OffsetX, OffsetY) <= BlastRadius)
		{
			OutTargets.AddUnique(Other);
		}
	}
}

void UChessAttackRule::CollectHorseTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	if (!CurrentActor || !Board)
	{
		return;
	}

	const int32 X = FMath::RoundToInt(CurrentActor->GetBoardPoint().X);
	const int32 Y = FMath::RoundToInt(CurrentActor->GetBoardPoint().Y);
	const EChessCamp Camp = CurrentActor->GetChessCamp();
	const int32 Offsets[8][2] = {
		{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
		{2, 1}, {2, -1}, {-2, 1}, {-2, -1}
	};

	for (const int32 (&Offset)[2] : Offsets)
	{
		const int32 TargetX = X + Offset[0];
		const int32 TargetY = Y + Offset[1];
		if (!ChessBoard::IsInside(TargetX, TargetY))
		{
			continue;
		}

		const int32 LegX = X + (FMath::Abs(Offset[0]) == 2 ? FMath::Sign(Offset[0]) : 0);
		const int32 LegY = Y + (FMath::Abs(Offset[1]) == 2 ? FMath::Sign(Offset[1]) : 0);
		if (IsValid(FindPieceAtCell(Board, LegX, LegY)))
		{
			continue;
		}

		AChessPoint* Other = FindPieceAtCell(Board, TargetX, TargetY);
		if (IsValid(Other) && Other->GetChessCamp() != Camp)
		{
			OutTargets.AddUnique(Other);
		}
	}
}

void UChessAttackRule::CollectObiitTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	CollectPawnForwardTarget(CurrentActor, Board, OutTargets);
}

void UChessAttackRule::CollectSoldierTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	CollectPawnForwardTarget(CurrentActor, Board, OutTargets);
}
