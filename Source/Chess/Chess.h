// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// 棋子类型
UENUM(Blueprintable)
enum class EChessType : uint8
{
	ECT_Boss		UMETA(DisplayName = "Boss(帅)"),
	ECT_Soldier		UMETA(DisplayName = "Soldier(士兵)"),
	ECT_Elephant	UMETA(DisplayName = "Elephant(象)"),
	ECT_Horse		UMETA(DisplayName = "Horse(马)"),
	ECT_Car			UMETA(DisplayName = "Car(车)"),
	ECT_Cannon		UMETA(DisplayName = "Cannon(炮)"),
	ECT_Obiit		UMETA(DisplayName = "Obiit(卒)"),
	ECT_MAX
};

// 棋子阵容
UENUM(Blueprintable)
enum class EChessCamp : uint8
{
	ECT_Red			UMETA(DisplayName = "Red(红方)"),
	ECT_Blue		UMETA(DisplayName = "Blue(蓝方)"),
	ECT_MAX
};

// 当前回合
UENUM(Blueprintable)
enum class EChessTurn : uint8
{
	EXT_Red			UMETA(DisplayName = "Red"),
	EXT_Blue		UMETA(DisplayName = "Blue"),
	EXT_MAX
};

/**
 *	
 *	9	车	象	马	士	帅	士	马	象	车	红方
 *	8
 *	7		炮						炮
 *	6	兵		兵		兵		兵		兵
 *	5
 *	4
 *	3	兵		兵		兵		兵		兵
 *	2		炮						炮
 *	1
 *	0	车	象	马	士	帅	士	马	象	车
 *		0	1	2	3	4	5	6	7	8	蓝方
 *	X/Y 
 */
namespace ChessBoard
{
	// ==================== 尺寸 ====================
	// 坐标单位为“格”：X 为列 0..8，Y 为行 0..9
	constexpr int32 Columns = 9;
	constexpr int32 Rows = 10;
	constexpr int32 CellCount = Columns * Rows;

	// ==================== 河界 ====================
	// 红方半场：Y <  RiverY
	// 蓝方半场：Y >= RiverY
	constexpr int32 RiverY = 5;

	// ==================== 九宫 ====================
	// 九宫的列范围对双方相同，行范围各自不同
	constexpr int32 PalaceMinY = 3;
	constexpr int32 PalaceMaxY = 5;

	constexpr int32 RedPalaceMinX = 7;
	constexpr int32 RedPalaceMaxY = 9;

	constexpr int32 BluePalaceMinX = 0;
	constexpr int32 BluePalaceMaxY = 2;

	// ==================== 判定工具 ====================

	/** 整数格坐标是否在棋盘内 */
	constexpr bool IsInside(int32 X, int32 Y)
	{
		return X >= 0 && X < Columns && Y >= 0 && Y < Rows;
	}

	/** 浮点格坐标是否在棋盘内（先四舍五入到整数格） */
	inline bool IsInside(const FVector2D& Cell)
	{
		return IsInside(FMath::RoundToInt(Cell.X), FMath::RoundToInt(Cell.Y));
	}

	/** 该行是否属于红方半场 */
	constexpr bool IsRedSide(int32 Y)
	{
		return Y < RiverY;
	}

	/** 该行是否属于蓝方半场 */
	constexpr bool IsBlueSide(int32 Y)
	{
		return Y >= RiverY;
	}
}