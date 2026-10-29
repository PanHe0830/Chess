// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChessAttackRule.generated.h"

class AChessPoint;
class AChessGameMode;
enum class EChessCamp : uint8;
/**
 * 
 */
UCLASS()
class CHESS_API UChessAttackRule : public UObject
{
	GENERATED_BODY()
public:
	virtual void CollectTargets(AChessPoint* CurrentActor,AChessGameMode* Board,TArray<AChessPoint*>& OutTargets) const;
};
