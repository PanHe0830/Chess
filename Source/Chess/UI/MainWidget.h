// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UOverlay;

/**
 * 
 */
UCLASS()
class CHESS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere , Category = "UI|MainWidget" , meta = (BindWidget))
	UOverlay* ChessDetailOverlay;
};
