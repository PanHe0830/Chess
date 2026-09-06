// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessManagerSubsystem.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "Chess/Actor/ChessPoint.h"

void UChessManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadDataTables();
	LoadDataAssets();
}

void UChessManagerSubsystem::Deinitialize()
{
	SetCurrentSelectedActor(nullptr);
	Super::Deinitialize();
}

void UChessManagerSubsystem::SetCurrentSelectedActor(AActor* NewSelected)
{
	if (CurrentSelectedActor.Get() == NewSelected)
	{
		return;
	}

	if (AChessPoint* OldPiece = Cast<AChessPoint>(CurrentSelectedActor.Get()))
	{
		OldPiece->Deselect();
	}

	CurrentSelectedActor = NewSelected;

	if (AChessPoint* NewPiece = Cast<AChessPoint>(NewSelected))
	{
		NewPiece->Select();
	}
}

AActor* UChessManagerSubsystem::GetCurrentSelectedActor() const
{
	return CurrentSelectedActor.Get();
}

UDataTable* UChessManagerSubsystem::GetDataTableByName(const FName TableName)
{
	if (TableConfigMap.Num() <= 0 || TableName.IsNone()) return nullptr;
	
	return Cast<UDataTable>(TableConfigMap[TableName]);
}

UDataAsset* UChessManagerSubsystem::GetDataAssetByName(const FName TableName)
{
	if (AssetConfigMap.Num() <= 0 || TableName.IsNone()) return nullptr;
	
	return Cast<UDataAsset>(AssetConfigMap[TableName]);
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
	Filter.ClassPaths.Add(UPrimaryDataAsset::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;

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