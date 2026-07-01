// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessManagerSubsystem.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Chess/Actor/ChessBoard.h"
#include "Chess/DataAsset/ChessConfig.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "Chess/Datatable/ChessPointConfig.h"
#include "Chess/Actor/ChessPoint.h"

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
	//SpawnChessBoard();
	//SpawnChessPoint();
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


void UChessManagerSubsystem::SpawnChessBoard(FVector& Position , FRotator& Rotation , float Distance)
{
	if (UDataAsset* Table = AssetConfigMap.FindRef(FName("DA_ChessConfig")))
	{
		if (UChessConfig* ChessConfig = Cast<UChessConfig>(Table))
		{
			TSubclassOf<AActor> BoardClass = ChessConfig->ChessBoard;
			if (BoardClass)
			{
				SpwanChessBoards(BoardClass , Position , Rotation , Distance);
			}
		}
	}
}

void UChessManagerSubsystem::SpawnChessPoint(FVector& Position, float Distance)
{
	if (UDataAsset* Table = AssetConfigMap.FindRef(FName("DA_ChessConfig")))
	{
		if (UChessConfig* ChessConfig = Cast<UChessConfig>(Table))
		{
			TSubclassOf<AActor> PointClass = ChessConfig->ChessPoint;
			if (PointClass)
			{
				SpawnChessPoints(PointClass,Position,Distance);
			}
		}
	}
}

void UChessManagerSubsystem::SpwanChessBoards(TSubclassOf<AActor> BoardClass , FVector& Position , FRotator& Rotation , float Distance)
{
	AActor* SpawnActor =  nullptr;
	
	UWorld* World = GetWorld();
	if (World)
	{
		for (int i = 0;i<9;i++)
		{
			for (int j = 0;j<10;j++)
			{
				FVector NewPosition = FVector(Position.X + i*Distance,Position.Y + j*Distance,Position.Z);
				SpawnActor = World->SpawnActor<AActor>(BoardClass,NewPosition,Rotation);
				if (SpawnActor)
				{
					AChessBoard* ChessBoard = Cast<AChessBoard>(SpawnActor);
					if (ChessBoard)
					{
						ChessBoard->SetBoardPoint(FVector2D(i,j));
						
					}
				}
			}
		}
		
	}
	
}

void UChessManagerSubsystem::SpawnChessPoints(TSubclassOf<AActor> PointClass,FVector Position , float Distance)
{
	if (!PointClass) return;
	FVector NewPosition = Position;
	UWorld* World = GetWorld();
	if (!World) return;
	AActor* SpawnActor =  nullptr;
	
	if (UDataTable* Table = TableConfigMap.FindRef(FName("DT_ChessPointConfig")))
	{
		TArray<FChessPointConfig*> AssetList;
		Table->GetAllRows<FChessPointConfig>(TEXT("DT_ChessPointConfig"),AssetList);
		if (AssetList.Num() <= 0) return;
		for (const FChessPointConfig* ChessPointConfig : AssetList)
		{
			UStaticMesh* Mesh = ChessPointConfig->ChessMesh.LoadSynchronous();
			if (!Mesh) return;
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
			AChessPoint* ChessActor = World->SpawnActor<AChessPoint>(
				AChessPoint::StaticClass(),
				NewPosition,
				FRotator(),
				SpawnParams
			);
    
			if (ChessActor)
			{
				ChessActor->SetMesh(Mesh);
			}
		}
	}
}