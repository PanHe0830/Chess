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