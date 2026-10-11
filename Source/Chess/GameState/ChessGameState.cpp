// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameState.h"

#include "Net/UnrealNetwork.h"

void AChessGameState::ChangeChessTurn()
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentTurn =
		CurrentTurn == EChessTurn::EXT_Red
		? EChessTurn::EXT_Blue
		: EChessTurn::EXT_Red;
}

void AChessGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AChessGameState, CurrentTurn);
}
