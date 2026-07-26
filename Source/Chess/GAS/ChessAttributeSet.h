// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ChessAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:	
	UChessAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UChessAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UChessAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UChessAttributeSet, AttackDamage);
	
	// 手动修改会进入PreAttributeChange
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// 执行GameplayEffect会进入PostGameplayEffectExecute
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
