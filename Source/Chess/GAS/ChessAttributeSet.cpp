// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"

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
	
	if (Data.EvaluatedData.Attribute != GetHealthAttribute())
	{
		return;
	}
	// Instant GE 后 CurrentValue 已是新血量
	if (GetHealth() > 0.f)
	{
		return;
	}
	AActor* Owner = GetOwningActor();
	if (!Owner || !Owner->HasAuthority())
	{
		return; // 只在服务器销毁
	}
	AChessPoint* Piece = Cast<AChessPoint>(Owner);
	if (!Piece)
	{
		return;
	}
	if (UWorld* World = Piece->GetWorld())
	{
		if (AChessGameMode* GM = World->GetAuthGameMode<AChessGameMode>())
		{
			GM->RemoveChessPoint(Piece); // 先清 PieceMap
		}
	}
	Piece->Destroy(); // EndPlay 里若再 Remove 一般也安全
}
