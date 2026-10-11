// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UIConfig.generated.h"


// 棋子配置
USTRUCT(BlueprintType)
struct FUIConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = UI)
	FName UIName;
	
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> UINameWidget;
};