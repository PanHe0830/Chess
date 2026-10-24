// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessMoveBase.h"
#include "Chess/Chess.h"
#include "ChessMoveObiit.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessMoveObiit : public UChessMoveBase
{
	GENERATED_BODY()
public:
	virtual bool IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
		const TArray<FVector2D>& OccupiedCells) const override;
};
