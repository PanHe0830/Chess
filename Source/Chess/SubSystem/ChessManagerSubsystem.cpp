// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessManagerSubsystem.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Chess/DataAsset/ChessConfig.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"

void UChessManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadDataTables();
	LoadDataAssets();
}

void UChessManagerSubsystem::SpawnChessBoardAndPoint()
{
	if (TableConfigMap.IsEmpty() || AssetConfigMap.IsEmpty())
	{
		UE_LOG(LogTemp , Warning, TEXT("No TableConfig or AssetConfigMap or AssetConfigMap."));
	}
	SpawnChessBoard();
	SpawnChessPoint();
}

void UChessManagerSubsystem::LoadDataTables()
{
	TableConfigMap.Empty();
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter Filter;
	Filter.PackagePaths.Add(TableConfig::TablePath);   // 指定目录
	Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;

	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssets(Filter, AssetList);

	for (const FAssetData& AssetData : AssetList)
	{
		UDataTable* DataTable = Cast<UDataTable>(AssetData.GetAsset());

		if (DataTable)
		{
			TableConfigMap.Add(DataTable->GetFName(),DataTable);

			UE_LOG(LogTemp, Log,TEXT("Load DataTable : %s"),*DataTable->GetName());
		}
	}
}

void UChessManagerSubsystem::LoadDataAssets()
{
	AssetConfigMap.Empty();
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter Filter;
	Filter.PackagePaths.Add(AssetConfig::AssetPath);   // 指定目录
	Filter.ClassPaths.Add(UDataAsset::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;

	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssets(Filter, AssetList);

	for (const FAssetData& AssetData : AssetList)
	{
		UDataAsset* DataAsset = Cast<UDataAsset>(AssetData.GetAsset());

		if (DataAsset)
		{
			AssetConfigMap.Add(DataAsset->GetFName(),DataAsset);

			UE_LOG(LogTemp, Log,TEXT("Load DataTable : %s"),*DataAsset->GetName());
		}
	}
}

bool UChessManagerSubsystem::SpawnChessBoard(FVector& Position , FRotator& Rotation)
{
	AActor* SpawnActor =  nullptr;
	if (UDataAsset* Table = AssetConfigMap.FindRef(FName("DA_ChessConfig")))
	{
		if (UChessConfig* ChessConfig = Cast<UChessConfig>(Table))
		{
			TSubclassOf<AActor> BoardClass = ChessConfig->ChessBoard;
			if (BoardClass)
			{
				SpawnActor = GetWorld()->SpawnActor<AActor>(BoardClass,Position,Rotation);
			}
		}
	}
	
	return SpawnActor == nullptr;
}

void UChessManagerSubsystem::SpawnChessPoint(float Distance)
{
	if (UDataAsset* Table = AssetConfigMap.FindRef(FName("DA_ChessConfig")))
	{
		if (UChessConfig* ChessConfig = Cast<UChessConfig>(Table))
		{
			TSubclassOf<AActor> PointClass = ChessConfig->ChessPoint;
			if (PointClass)
			{
				
			}
		}
	}
}
