// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Chess/Chess.h"
#include "ChessConfig.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	// 棋盘类
	UPROPERTY(EditAnywhere , Category = Chess)
	TSubclassOf<AActor> ChessBoard;
	
	// 棋子类
	UPROPERTY(EditAnywhere , Category = Chess)
	TSubclassOf<AActor> ChessPoint;
};
