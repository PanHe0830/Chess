// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessMoveBase.h"
#include "Chess/Chess.h"
#include "ChessMoveCar.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessMoveCar : public UChessMoveBase
{
	GENERATED_BODY()
public:
	bool IsMoveLegal(EChessCamp Camp , const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells) const;
};
