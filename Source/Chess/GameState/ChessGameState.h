// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Chess/Chess.h"
#include "ChessGameState.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	EChessTurn CurrentTurn = EChessTurn::EXT_Red;
	
	void ChangeChessTurn();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
