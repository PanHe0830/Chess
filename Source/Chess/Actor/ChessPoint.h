// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPoint.generated.h"

UCLASS()
class CHESS_API AChessPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AChessPoint();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
};
