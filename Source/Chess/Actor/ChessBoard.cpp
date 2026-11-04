// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"

#include "Components/StaticMeshComponent.h"

AChessBoard::AChessBoard()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	BoardPoint = FVector2D(0,0);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	SetRootComponent(StaticMesh);
	// 仅 Query：可被点选，不阻挡棋子滑动
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AChessBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessBoard::SetBoardPoint(FVector2D point)
{
	BoardPoint = point;
}

FVector2D AChessBoard::GetBoardPoint() const
{
	return BoardPoint;
}

void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

