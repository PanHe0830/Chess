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

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_BoardPoint , EditAnywhere , Category = "ChessBoard")
	FVector2D BoardPoint;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UStaticMeshComponent* StaticMesh;
	
	UFUNCTION()
	void OnRep_BoardPoint();
};
