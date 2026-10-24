// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveSoldier.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveSoldier::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& /*OccupiedCells*/) const
{
	// 兵/卒不需要路径判断，直接复用通用走法：未过河只能前进，过河后可横走一步
	return UChessStaticFun::IsPawnMove(Camp, From, To);
}
