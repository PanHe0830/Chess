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

void UChessAttackRule::CollectCarTargets(AChessPoint* CurrentActor,AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	if (!CurrentActor || !Board)
	{
		return;
	}
	const EChessCamp Camp = CurrentActor->GetChessCamp();
	const FVector2D From = CurrentActor->GetBoardPoint();
	const int32 FX = FMath::RoundToInt(From.X);
	const int32 FY = FMath::RoundToInt(From.Y);
	const FIntPoint Dirs[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	// 一方向最多走这么多步（不会超出棋盘）
	const int32 MaxSteps = FMath::Max(ChessBoard::Columns, ChessBoard::Rows);
	for (const FIntPoint& Dir : Dirs)
	{
		for (int32 Step = 1; Step < MaxSteps; ++Step)
		{
			const int32 X = FX + Dir.X * Step;
			const int32 Y = FY + Dir.Y * Step;
			if (!ChessBoard::IsInside(X, Y))
			{
				break; // 出界，换下一个方向
			}
			AChessPoint* Other = Board->GetPieceAt(FVector2D(X, Y));
			if (!Other)
			{
				continue; // 空格，继续往远处看
			}
			if (Other->GetChessCamp() != Camp)
			{
				OutTargets.AddUnique(Other);
			}
			break; // 碰到子（敌或己）就停这个方向
		}
	}
}

PRAGMA_ENABLE_OPTIMIZATION