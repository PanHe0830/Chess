// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChessGameMode.generated.h"

class AChessBoard;
class AChessPoint;
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
	virtual void PostLogin(APlayerController* NewPlayer) override;
public:
	virtual void Tick( float DeltaTime ) override;
	
protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
private:
	void SpawnChessBoard();
	void SetChessPoint();
	void StartChessGameModeTimer();
	void StopChessGameModeTimer();
	void ChangeChessTurn();
	void CloseReadyWidgets();

	bool bMatchStarted = false;
	int32 AssignedPlayerCount = 0;
public:
	void NotifyPlayerReady();
	void RegisterChessPoint(AChessPoint* Point);
	void UpdateChessPointPosition(AChessPoint* Point, const FVector2D& NewPoint);
	void RemoveChessPoint(AChessPoint* Point);
	TArray<FVector2D> GetOccupiedCells() const;
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
	float TurnDuration = 10.0f;
private:
	UPROPERTY(VisibleAnywhere, Category = "Chess")
	TMap<FVector2D , TObjectPtr<AChessBoard>> BoardMap;

	UPROPERTY(VisibleAnywhere, Category = "Chess")
	TMap<FVector2D, TObjectPtr<AChessPoint>> PieceMap;
	
	FTimerHandle TimerHandle;
};
