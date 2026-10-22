// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Chess/Chess.h"
#include "GameFramework/Actor.h"
#include "ChessPoint.generated.h"

class UChessMoveBase;
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
	void SetBoardPoint(const FVector2D& InBoardPoint);
	FVector2D GetBoardPoint() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessType ChessType = EChessType::ECT_MAX;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessCamp ChessCamp = EChessCamp::ECT_MAX;

	UPROPERTY(Replicated, VisibleAnywhere, Category = ChessPoint)
	FVector2D BoardPoint = FVector2D::ZeroVector;

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
	
	UFUNCTION(BlueprintCallable, Category="Ability System")
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability);
	// ====================================GAS====================================
	
	void SetChessMoveRule(UObject* InMoveRule);
	void SetAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);
	UChessMoveBase* GetChessMoveRule() const { return MoveRule; }
private:
	UPROPERTY(VisibleAnywhere, Category = "Rule|Move")
	TObjectPtr<UChessMoveBase> MoveRule;

	UPROPERTY()
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};
