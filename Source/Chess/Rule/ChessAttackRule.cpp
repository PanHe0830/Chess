// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttackRule.h"

#include "Chess/Chess.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"

void UChessAttackRule::CollectTargets(EChessCamp Camp, const FVector2D& Cell, AChessGameMode* Board,
                                      TArray<AChessPoint*>& OutTargets) const
{
	const int32 Forward = (Camp == EChessCamp::ECT_Red) ? 1 : -1;
	const FVector2D Front(Cell.X, Cell.Y + Forward);
	if (AChessPoint* Other = Board->GetPieceAt(Front))
	{
		if (Other->GetChessCamp() != Camp)
		{
			OutTargets.Add(Other);
		}
	}
}
