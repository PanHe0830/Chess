// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveObiit.h"

#include "Chess/FunCore/UChessStaticFun.h"

bool UChessMoveObiit::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& /*OccupiedCells*/) const
{
	// 卒的走法与兵完全一致（方向由 Camp 决定），所以同样复用 IsPawnMove。
	// 如果 Obiit 在你的设计里其实代表“士/仕”，这里要改成九宫内的斜走一步。
	return UChessStaticFun::IsPawnMove(Camp, From, To);
}
