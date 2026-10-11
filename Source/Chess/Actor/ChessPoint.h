// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Chess/Chess.h"
#include "GameFramework/Actor.h"
#include "ChessPoint.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UChessAttributeSet;

UCLASS()
class CHESS_API AChessPoint : public AActor , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AChessPoint();

	virtual void Tick(float DeltaTime) override;
	
	void SetMesh(UStaticMesh* Mesh);

	void Select();
	void Deselect();
	bool IsSelected() const { return bIsSelected; }
	EChessCamp GetChessCamp() const { return ChessCamp; }
	FVector GetLogicalLocation() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessType ChessType = EChessType::ECT_MAX;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessCamp ChessCamp = EChessCamp::ECT_MAX;

	UPROPERTY(EditAnywhere, Category = ChessPoint)
	float SelectHeight = 50.f;

	bool bIsSelected = false;
	
	// ====================================GAS====================================
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UAbilitySystemComponent* GameAbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UChessAttributeSet* AttributeSet;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	TSubclassOf<UGameplayAbility> MoveAbility;
	
	UFUNCTION(BlueprintCallable, Category="Ability System")
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability);
	// ====================================GAS====================================
};
