// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPoint.h"
#include "Chess/ChessGamePlayTag.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "Chess/GAS/ChessAttributeSet.h"

AChessPoint::AChessPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GameAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("GameAbilitySystemComponent"));
	
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

void AChessPoint::BeginPlay()
{
	Super::BeginPlay();
	
	GameAbilitySystemComponent->InitAbilityActorInfo(this,this);
	const FGameplayAbilitySpec MoveSpec = GameAbilitySystemComponent->BuildAbilitySpecFromClass(MoveAbility,0,-1);
	const FGameplayAbilitySpecHandle Handle = GameAbilitySystemComponent->GiveAbility(MoveSpec);
	GameAbilitySystemComponent->TryActivateAbility(Handle);
	//const FGameplayAbilitySpecHandle Handle = GameAbilitySystemComponent->GiveAbility(MoveSpec);
	//GameAbilitySystemComponent->TryActivateAbility(Handle);
	//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,ChessGameplayTags::Chess_Move,FGameplayEventData());
}

UAbilitySystemComponent* AChessPoint::GetAbilitySystemComponent() const
{
	return GameAbilitySystemComponent;
}

