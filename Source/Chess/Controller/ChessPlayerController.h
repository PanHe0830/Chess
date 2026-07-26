// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class CHESS_API AChessPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void MouseLeftButtonClicked(const FInputActionValue& Value);
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Input")
	TObjectPtr<UInputAction> MouseDown;
};
