// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Chess/Chess.h"
#include "GameFramework/Actor.h"
#include "ChessPoint.generated.h"

class UChessAttackRule;
class UChessMoveBase;
class UGameplayAbility;
class UAbilitySystemComponent;
class UChessAttributeSet;

UCLASS()
class CHESS_API AChessPoint : public AActor , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	AChessPoint();
	
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetMesh(UStaticMesh* Mesh);

	void Select();
	void Deselect();
	FVector GetLogicalLocation() const;
	void SetBoardPoint(const FVector2D& InBoardPoint);
	bool IsActorSelected() const { return bIsSelected; }
	FVector2D GetBoardPoint() const {return BoardPoint;};
	UChessMoveBase* GetChessMoveRule() const { return MoveRule; }
	UChessAttackRule* GetChessAttackRule() const { return AttackRule; }
	EChessType GetChessType() const { return ChessType; }
	EChessCamp GetChessCamp() const { return ChessCamp; }
	
	void SetChessMoveRule(UObject* InMoveRule);
	void SetAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);
	void SetChessCamp(EChessCamp InChessCamp);
	void SetChessType(EChessType InChessType);
	void SetChessAttackRule(UObject* InMoveRule);
	
private:
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessType ChessType = EChessType::ECT_MAX;
	
	UPROPERTY(EditAnywhere, Category = ChessPoint)
	EChessCamp ChessCamp = EChessCamp::ECT_MAX;
	
	UPROPERTY(VisibleAnywhere, Category = "Rule|Move")
	TObjectPtr<UChessMoveBase> MoveRule;
	
	UPROPERTY(VisibleAnywhere, Category = "Rule|Move")
	TObjectPtr<UChessAttackRule> AttackRule;

	UPROPERTY(Replicated, VisibleAnywhere, Category = ChessPoint)
	FVector2D BoardPoint = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, Category = ChessPoint)
	float SelectHeight = 50.f;

	bool bIsSelected = false;

	UPROPERTY()
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	
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
};
