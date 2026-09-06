// Fill out your copyright notice in the Description page of Project Settings.


#include "UChessStaticFun.h"

void UChessStaticFun::PrintStringMessage(FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
}
