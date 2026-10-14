// Fill out your copyright notice in the Description page of Project Settings.


#include "UChessStaticFun.h"

void UChessStaticFun::PrintStringMessage(FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
}

bool UChessStaticFun::IsStraightLine(const FVector2D& From, const FVector2D& To)
{
	const int32 DeltaX = FMath::Abs(FMath::RoundToInt(To.X - From.X));
	const int32 DeltaY = FMath::Abs(FMath::RoundToInt(To.Y - From.Y));
	return (DeltaY + DeltaX) == 1 ? true : false;
}
