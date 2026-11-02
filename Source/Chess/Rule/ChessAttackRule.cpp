// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttackRule.h"

#include "Chess/Chess.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"
PRAGMA_DISABLE_OPTIMIZATION
void UChessAttackRule::CollectTargets(AChessPoint* CurrentActor,AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	EChessCamp Camp = CurrentActor->GetChessCamp();
	EChessType Type = CurrentActor->GetChessType();
	const int32 Forward = (Camp == EChessCamp::ECT_Red) ? 1 : -1;
	FVector2D CellPos = CurrentActor->GetBoardPoint();
	switch (Type)
	{
	case EChessType::ECT_Boss:
			
		break;
	case EChessType::ECT_Soldier:
			
		break;
	case EChessType::ECT_Elephant:
			
		break;
	case EChessType::ECT_Horse:
			
		break;
	case EChessType::ECT_Car:
		CollectCarTargets(CurrentActor, Board,OutTargets);
		break;
	case EChessType::ECT_Cannon:
			
		break;
	case EChessType::ECT_Obiit:
			
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

	const TMap<FVector2D, TObjectPtr<AChessPoint>> Occupied = Board->GetOccupiedPoints();
	for (const TPair<FVector2D, TObjectPtr<AChessPoint>>& Pair : Occupied)
	{
		AChessPoint* Other = Pair.Value.Get();
		if (!IsValid(Other))
		{
			continue;
		}

		// 排除自己与同阵营
		if (Other == CurrentActor || Other->GetChessCamp() == Camp)
		{
			continue;
		}

		const int32 OtherX = FMath::RoundToInt(Pair.Key.X);
		const int32 OtherY = FMath::RoundToInt(Pair.Key.Y);
		const int32 OffsetX = OtherX - ToX;
		const int32 OffsetY = OtherY - ToY;

		// 必须在「落点」沿移动方向的射线上，且距离 1~10 格
		if (DirX != 0)
		{
			if (OffsetY != 0 || FMath::Sign(OffsetX) != DirX)
			{
				continue;
			}
			if (FMath::Abs(OffsetX) > MaxRange)
			{
				continue;
			}
		}
		else // DirY != 0
		{
			if (OffsetX != 0 || FMath::Sign(OffsetY) != DirY)
			{
				continue;
			}
			if (FMath::Abs(OffsetY) > MaxRange)
			{
				continue;
			}
		}

		OutTargets.AddUnique(Other);
	}
}

PRAGMA_ENABLE_OPTIMIZATION