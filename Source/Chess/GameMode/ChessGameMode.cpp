// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

#include "Chess/Actor/ChessBoard.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/Datatable/ChessPointConfig.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"


void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnChessBoard();
	SetChessPoint();
}

void AChessGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (BoardMap.Num() > 0)
	{
		for (auto& Pair : BoardMap)
		{
			if (IsValid(Pair.Value))
			{
				Pair.Value->Destroy();
			}
		}
		BoardMap.Empty();
	}
}

void AChessGameMode::SpawnChessBoard()
{
	if (ChessBoardX <= 0 || ChessBoardY <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Chess Board"));
		return;
	}
	
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for (int32 X = 0; X < ChessBoardX; ++X)
	{
		for (int32 Y = 0; Y < ChessBoardY; ++Y)
		{
			const FVector SpawnLocation(
				ChessBoardInit + X * ChessBoardScale,
				ChessBoardInit + Y * ChessBoardScale,
				0.f);
			const FRotator SpawnRotation = FRotator::ZeroRotator;
			AChessBoard* Board = World->SpawnActor<AChessBoard>(
				ChessBoardClass,
				SpawnLocation,
				SpawnRotation,
				SpawnParams);
			if (Board)
			{
				Board->SetBoardPoint(FVector2D(X, Y));
				BoardMap.Add(FVector2D(X, Y), Board);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Can't SpawnChessBoard"));
			}
		}
	}
}

void AChessGameMode::SetChessPoint()
{
	UWorld* World = GetWorld();
	
	if (World == nullptr) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
	{
		if (UDataTable* Table = ChessManager->GetDataTableByName("DT_ChessPointConfig"))
		{
			TArray<FChessPointConfig*> AllRows;
			Table->GetAllRows<FChessPointConfig>(TEXT("SetChessPoint"),AllRows);
			for (const FChessPointConfig* Row : AllRows)
			{
				if (!Row) continue;
				
				if (BoardMap.Find(Row->ChessLocation) && Row->ChessActor)
				{
					const FRotator SpawnRotation = FRotator::ZeroRotator;
					AChessPoint* Point = World->SpawnActor<AChessPoint>(Row->ChessActor,BoardMap.Find(Row->ChessLocation)->Get()->GetActorLocation(),SpawnRotation,SpawnParams);
					if (!Point)
					{
						UE_LOG(LogTemp, Warning, TEXT("Can't SpawnChessPoint"));
					}
				}
			}
		}
	}
}
