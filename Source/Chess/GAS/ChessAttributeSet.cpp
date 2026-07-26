// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttributeSet.h"

UChessAttributeSet::UChessAttributeSet()
{
	Health = FGameplayAttributeData(3.0f);
	MaxHealth = FGameplayAttributeData(3.0f);
	AttackDamage = FGameplayAttributeData(1.0f);
}

void UChessAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue =  FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UChessAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	
}
