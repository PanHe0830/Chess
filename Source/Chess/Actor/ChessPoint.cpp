// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPoint.h"

#include "Components/StaticMeshComponent.h"

AChessPoint::AChessPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
}

void AChessPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessPoint::SetMesh(UStaticMesh* Mesh)
{
	StaticMesh->SetStaticMesh(Mesh);
}

void AChessPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

