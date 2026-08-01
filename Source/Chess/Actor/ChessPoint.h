// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
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
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UStaticMeshComponent* StaticMesh;
	
	// ====================================GAS====================================
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UAbilitySystemComponent* GameAbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UChessAttributeSet* AttributeSet;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	TSubclassOf<UGameplayAbility> MoveAbility;
	// ====================================GAS====================================
};
