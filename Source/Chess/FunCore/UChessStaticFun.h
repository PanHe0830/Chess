// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chess.h"

/**
 * 棋盘相关的纯函数工具集。
 * 全部为 static、无状态，方便在走法规则里复用，也方便单独测试。
 */
class CHESS_API UChessStaticFun
{
public:
	UChessStaticFun() = delete;
	~UChessStaticFun() = delete;
	
	static void PrintStringMessage(FString message);
	static bool IsStraightLine(const FVector2D& From, const FVector2D& To);
	static bool HasPieceOnPath(const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells);

	/** 两个格子是否为同一格（先四舍五入到整数格，避免浮点误差） */
	static bool IsSameCell(const FVector2D& A, const FVector2D& B);

	/** 该格子上是否已经有棋子 */
	static bool IsCellOccupied(const FVector2D& Cell, const TArray<FVector2D>& OccupiedCells);

	/**
	 * 统计 From 与 To 之间（不含两端）有子的格子数量，炮的“隔子”判断用。
	 * 只对同行或同列的直线调用；传入斜线时返回 -1 表示用法有误。
	 */
	static int32 CountPiecesBetween(const FVector2D& From, const FVector2D& To, const TArray<FVector2D>& OccupiedCells);

	/** 兵/卒走法：未过河只能向前一步，过河后可以向前或左右横走一步 */
	static bool IsPawnMove(EChessCamp Camp, const FVector2D& From, const FVector2D& To);
};
