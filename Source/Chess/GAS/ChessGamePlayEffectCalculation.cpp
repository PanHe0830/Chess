// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGamePlayEffectCalculation.h"

#include "ChessAttributeSet.h"

namespace
{
	struct FChessDamageCapture
	{
		DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage);
		DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

		FChessDamageCapture()
		{
			DEFINE_ATTRIBUTE_CAPTUREDEF(UChessAttributeSet, AttackDamage, Source, false);
			DEFINE_ATTRIBUTE_CAPTUREDEF(UChessAttributeSet, Health, Target, false);
		}
	};

	const FChessDamageCapture& ChessDamageCapture()
	{
		static FChessDamageCapture Capture;
		return Capture;
	}
}

UChessGamePlayEffectCalculation::UChessGamePlayEffectCalculation()
{
	RelevantAttributesToCapture.Add(ChessDamageCapture().AttackDamageDef);
	RelevantAttributesToCapture.Add(ChessDamageCapture().HealthDef);
}

void UChessGamePlayEffectCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
//	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
//
//	FAggregatorEvaluateParameters EvaluateParams;
//	EvaluateParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
//	EvaluateParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
//
//	float AttackDamage = 0.f;
//	float TargetHealth = 0.f;
//	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
//		ChessDamageCapture().AttackDamageDef, EvaluateParams, AttackDamage);
//	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
//		ChessDamageCapture().HealthDef, EvaluateParams, TargetHealth);
//
//	const float Damage = FMath::Max(0.f, AttackDamage - TargetHealth * 0.1f);
//	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
//		UChessAttributeSet::GetHealthAttribute(),
//		EGameplayModOp::Additive,
//		-Damage));
}
