// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChessHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void DrawHUD() override;
private:
	void InitializeGameMainWidget();
	
	UPROPERTY(EditAnywhere , Category = "HUD")
	TSubclassOf<class UUserWidget> MainWidget;
};
