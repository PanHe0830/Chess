// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ChessManagerSubsystem.generated.h"

namespace TableConfig
{
	const static FName TablePath = TEXT("/Game/DataTable/");
	const static FName TableName = TEXT("DT_ChessPointConfig");
}

namespace AssetConfig
{
	const static FName AssetPath = TEXT("/Game/DataAsset/");
	const static FName AssetName = TEXT("DA_ChessConfig");
}

class UDataTable;
class UDataAsset;
class AChessBoard;

/**
 * 
 */
UCLASS()
class CHESS_API UChessManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SpawnChessBoardAndPoint();
	
	AActor* GetChessBoard() {return ChessBoard;} 
	AActor* GetChessPoint() {return ChessPoint;}
	
	void SpawnChessBoard(FVector& Position , FRotator& Rotation);
	void SpawnChessPoint(FVector& Position , float Distance);
	
private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UDataTable>> TableConfigMap;
	
	UPROPERTY()
	TMap<FName, TObjectPtr<UDataAsset>> AssetConfigMap;
	
	UPROPERTY()
	TObjectPtr<AActor> ChessBoard;
	
	UPROPERTY()
	TObjectPtr<AActor> ChessPoint;
	
private:
	void LoadDataTables();
	void LoadDataAssets();
	void SpwanChessBoards(TSubclassOf<AActor> BoardClass , FVector& Position , FRotator& Rotation , float Distance);
	void SpawnChessPoints(TSubclassOf<AActor> PointClass,FVector Position,float Distance);
};
