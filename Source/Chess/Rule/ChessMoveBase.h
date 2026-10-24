// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chess.h"
#include "UObject/Object.h"
#include "ChessMoveBase.generated.h"

/**
 * 走子规则的共同基类。
 *
 * 重要：所有具体规则都必须重写 IsMoveLegal，并且参数列表要和这里“完全一致”。
 * C++ 里参数不一致的成员函数不是重写(override)而是重载(overload)，
 * 通过 UChessMoveBase* 调用时只会调到基类版本，派生类里的判断根本不会执行。
 * 因此派生类声明一律加 override，让编译器帮你检查签名是否写错。
 *
 * 注意：本层目前只做“几何规则”判断（走法形状 + 路径/马腿/象眼阻挡）。
 * “目标格是敌方还是己方棋子”“目标格是否有子”这类信息目前拿不到，
 * 因为参数里只有“有子的格子”而没有“格子上的阵营”。
 * 后续如果需要“不能吃自己的子”，应把 OccupiedCells 换成带阵营的棋盘查询接口。
 */
UCLASS()
class CHESS_API UChessMoveBase : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * 判断一步走子是否符合该棋子的走法规则。
	 *
	 * @param Camp           走子方阵营（兵/卒的前进方向、象的过河限制需要它）
	 * @param From           起点格。X 为列 0..8，Y 为行 0..9，红方在 Y 较小的一侧
	 * @param To             终点格
	 * @param OccupiedCells  当前棋盘上所有“有棋子”的格子（应包含 From 自身，空格不要放进来）
	 * @return 合法返回 true，非法返回 false
	 */
	virtual bool IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
		const TArray<FVector2D>& OccupiedCells) const;
};
