// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessPlayerController.generated.h"

struct FInputActionValue;
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
	virtual void AcknowledgePossession(APawn* P) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void MouseLeftButtonClicked(const FInputActionValue& Value);
	UFUNCTION()
	void MouseRightButtonClicked(const FInputActionValue& Value);
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Input")
	TObjectPtr<UInputAction> MouseLeftDown;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Input")
	TObjectPtr<UInputAction> MouseRightDown;
	
	UFUNCTION(Server, Reliable)
	void ServerRequestChessMove(class AChessPoint* Piece, FVector_NetQuantize TargetLocation,FVector2D Targert);

	UFUNCTION(Server, Reliable)
	void ServerNotifyReady();

	UFUNCTION(Client, Reliable)
	void ClientCloseReadyWidget();

	void SetStartViewRotation(const FRotator& NewRotation);

private:
	void ApplyStartViewRotation();

	UFUNCTION()
	void OnRep_StartViewRotation();

	UPROPERTY(ReplicatedUsing = OnRep_StartViewRotation)
	FRotator StartViewRotation;

	UPROPERTY(ReplicatedUsing = OnRep_StartViewRotation)
	bool bHasStartViewRotation = false;
};
