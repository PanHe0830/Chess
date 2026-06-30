// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Chess/Chess.h"
#include "ChessPointConfig.generated.h"


// 棋子配置
USTRUCT(BlueprintType)
struct FChessPointConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	// 棋子类型
	UPROPERTY(EditAnywhere, Category = Chess)
	EChessType ChessType;
	
	// 棋子阵营
	UPROPERTY(EditAnywhere, Category = Chess)
	EChessCamp ChessCamp;
	
	// 棋子网格体
	UPROPERTY(EditAnywhere, Category = Chess)
	TSoftObjectPtr<UStaticMesh> ChessMesh;
};