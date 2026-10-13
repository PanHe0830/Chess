// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chess.h"
#include "GameFramework/PlayerState.h"
#include "ChessPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChessCampChanged, EChessCamp, NewCamp);

/**
 * 
 */
UCLASS()
class CHESS_API AChessPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void SetReady(bool bNewReady);
	bool IsReady() const { return bReady; }

	void SetCamp(EChessCamp NewCamp);
	EChessCamp GetCamp() const { return Camp; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Camp();

	UPROPERTY(BlueprintAssignable)
	FOnChessCampChanged OnCampChanged;

private:
	UPROPERTY(Replicated)
	bool bReady = false;

	UPROPERTY(ReplicatedUsing = OnRep_Camp)
	EChessCamp Camp = EChessCamp::ECT_MAX;
};
