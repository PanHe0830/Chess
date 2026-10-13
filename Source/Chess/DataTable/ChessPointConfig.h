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
	
	// 棋子蓝图
	UPROPERTY(EditAnywhere, Category = Chess)
	TSubclassOf<AActor> ChessActor;
	
	// 棋子在棋盘上的位置
	UPROPERTY(EditAnywhere, Category = Chess)
	FVector2D ChessLocation;
	
	UPROPERTY(EditAnywhere, Category = Chess , DisplayName = "棋子移动规则配置")
	TSubclassOf<UObject> MoveRule;
	
	UPROPERTY(EditAnywhere, Category = Chess, DisplayName = "棋子技能")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};