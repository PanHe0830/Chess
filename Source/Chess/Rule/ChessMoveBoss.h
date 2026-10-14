// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chess.h"
#include "UObject/Object.h"
#include "ChessMoveBoss.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessMoveBoss : public UObject
{
	GENERATED_BODY()
public:
	bool IsMoveLegal(EChessCamp Camp , const FVector2D& From, const FVector2D& To) const;
};
