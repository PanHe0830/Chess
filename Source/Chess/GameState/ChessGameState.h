// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Chess/Chess.h"
#include "ChessGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChessTurnChanged, EChessTurn, NewTurn);
/**
 * 
 */
UCLASS()
class CHESS_API AChessGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly , ReplicatedUsing = OnRep_CurrentTurn)
	EChessTurn CurrentTurn = EChessTurn::EXT_Red;
	
	void ChangeChessTurn();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_CurrentTurn();
	
	UPROPERTY(BlueprintAssignable)
	FOnChessTurnChanged OnTurnChanged;
};
