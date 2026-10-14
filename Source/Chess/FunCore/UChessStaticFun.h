// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CHESS_API UChessStaticFun
{
public:
	UChessStaticFun() = delete;
	~UChessStaticFun() = delete;
	
	static void PrintStringMessage(FString message);
	static bool IsStraightLine(const FVector2D& From, const FVector2D& To);
};
