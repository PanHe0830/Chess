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
private:
	void SpawnChessBoard();
	
public:
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
private:
	UPROPERTY(VisibleAnywhere, Category = "Chess")
	TMap<FVector2D , TObjectPtr<AChessBoard>> BoardMap;
};
