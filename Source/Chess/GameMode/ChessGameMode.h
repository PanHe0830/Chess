// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChessGameMode.generated.h"

class AChessBoard;
/**
 * 
 */
UCLASS()
class CHESS_API AChessGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick( float DeltaTime ) override;
private:
	void SpawnChessBoard();
	void SetChessPoint();
	void StartChessGameModeTimer();
	void StopChessGameModeTimer();
	void ChangeChessTurn();
	void CloseReadyWidgets();

	bool bMatchStarted = false;
public:
	void NotifyPlayerReady();
	UPROPERTY(EditAnywhere , Category = "Chess")
	TSubclassOf<AChessBoard> ChessBoardClass;
	UPROPERTY(EditAnywhere , Category = "Chess")
	int32 ChessBoardX;
	UPROPERTY(EditAnywhere, Category = "Chess")
	int32 ChessBoardY;
	UPROPERTY(EditAnywhere, Category = "Chess")
	float ChessBoardInit = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Chess")
	float ChessBoardScale = 300.0f;
	// 回合切换时间
	UPROPERTY(EditAnywhere, Category = "Chess")
	float TurnDuration = 30.0f;
private:
	UPROPERTY(VisibleAnywhere, Category = "Chess")
	TMap<FVector2D , TObjectPtr<AChessBoard>> BoardMap;
	
	FTimerHandle TimerHandle;
};
