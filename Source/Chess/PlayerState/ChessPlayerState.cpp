// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerState.h"

#include "Net/UnrealNetwork.h"

void AChessPlayerState::SetReady(bool bNewReady)
{
	if (!HasAuthority())
	{
		return;
	}

	bReady = bNewReady;
}

void AChessPlayerState::SetCamp(EChessCamp NewCamp)
{
	if (!HasAuthority())
	{
		return;
	}

	Camp = NewCamp;
	OnRep_Camp();
}

void AChessPlayerState::OnRep_Camp()
{
	OnCampChanged.Broadcast(Camp);
}

void AChessPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChessPlayerState, bReady);
	DOREPLIFETIME(AChessPlayerState, Camp);
}

