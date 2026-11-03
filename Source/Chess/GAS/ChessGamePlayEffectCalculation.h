// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ChessGamePlayEffectCalculation.generated.h"

UCLASS()
class CHESS_API UChessGamePlayEffectCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UChessGamePlayEffectCalculation();

protected:
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
