// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPoint.h"

#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "Chess/GAS/ChessAttributeSet.h"
#include "Chess/GameMode/ChessGameMode.h"
#include "Net/UnrealNetwork.h"

AChessPoint::AChessPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GameAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("GameAbilitySystemComponent"));
	bReplicates = true;
	SetReplicatingMovement(true);
	GameAbilitySystemComponent->SetIsReplicated(true);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	AttributeSet = CreateDefaultSubobject<UChessAttributeSet>(FName("AttributeSet"));
}

void AChessPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessPoint::SetMesh(UStaticMesh* Mesh)
{
	StaticMesh->SetStaticMesh(Mesh);
}

void AChessPoint::Select()
{
	if (bIsSelected)
	{
		return;
	}

	bIsSelected = true;
	AddActorWorldOffset(FVector(0.f, 0.f, SelectHeight));
}

void AChessPoint::Deselect()
{
	if (!bIsSelected)
	{
		return;
	}

	bIsSelected = false;
	AddActorWorldOffset(FVector(0.f, 0.f, -SelectHeight));
}

FVector AChessPoint::GetLogicalLocation() const
{
	FVector Location = GetActorLocation();
	if (bIsSelected)
	{
		Location.Z -= SelectHeight;
	}
	return Location;
}

void AChessPoint::SetBoardPoint(const FVector2D& InBoardPoint)
{
	BoardPoint = InBoardPoint;
}

FVector2D AChessPoint::GetBoardPoint() const
{
	return BoardPoint;
}

void AChessPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChessPoint, BoardPoint);
}

void AChessPoint::BeginPlay()
{
	Super::BeginPlay();
	
	GameAbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (!HasAuthority())
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		GiveAbility(AbilityClass);
	}
}

void AChessPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (AChessGameMode* ChessGameMode = World->GetAuthGameMode<AChessGameMode>())
		{
			ChessGameMode->RemoveChessPoint(this);
		}
	}

	Super::EndPlay(EndPlayReason);
	
	if (IsValid(MoveRule) && !MoveRule->HasAnyFlags(RF_ClassDefaultObject))
	{
		MoveRule->MarkAsGarbage();
		MoveRule = nullptr;
	}
}

UAbilitySystemComponent* AChessPoint::GetAbilitySystemComponent() const
{
	return GameAbilitySystemComponent;
}

void AChessPoint::GiveAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if(GameAbilitySystemComponent)
	{
		if(HasAuthority() && Ability)
		{
			GameAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1));
		}
		GameAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AChessPoint::SetChessMoveRule(UObject* InMoveRule)
{
	MoveRule = InMoveRule;
}

void AChessPoint::SetAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities)
{
	Abilities = InAbilities;
}

