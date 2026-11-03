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

void UChessAttackRule::CollectCannonTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	
}

void UChessAttackRule::CollectElephantTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	
}

void UChessAttackRule::CollectHorseTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	
}

void UChessAttackRule::CollectObiitTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	
}

void UChessAttackRule::CollectSoldierTargets(AChessPoint* CurrentActor, AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	
}
