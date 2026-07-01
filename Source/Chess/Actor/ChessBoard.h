// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessBoard.generated.h"

UCLASS()
class CHESS_API AChessBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AChessBoard();
	
	virtual void Tick(float DeltaTime) override;
	
	void SetBoardPoint(FVector2D point);
	
	FVector2D GetBoardPoint() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere , Category = "ChessBoard")
	FVector2D BoardPoint;
};
