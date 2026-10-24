// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveBase.h"

bool UChessMoveBase::IsMoveLegal(EChessCamp Camp, const FVector2D& From, const FVector2D& To,
	const TArray<FVector2D>& OccupiedCells) const
{
	// 基类不假设任何棋子的走法，默认一律判为不合法（fail-closed）。
	// 这样即使以后新增了棋子类型但忘了配规则，表现是“走不动”，
	// 而不是“能走到棋盘任何地方”这种更难排查的问题。
	return false;
}
