// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttackRule.h"

#include "Chess/Chess.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"

void UChessAttackRule::CollectTargets(AChessPoint* CurrentActor,AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const
{
	EChessCamp Camp = CurrentActor->GetChessCamp();
	const int32 Forward = (Camp == EChessCamp::ECT_Red) ? 1 : -1;
	FVector2D CellPos = CurrentActor->GetBoardPoint();
	const FVector2D Front(CellPos.X, CellPos.Y + Forward);
	if (AChessPoint* Other = Board->GetPieceAt(Front))
	{
		if (Other->GetChessCamp() != Camp)
		{
			OutTargets.Add(Other);
		}
	}
}
