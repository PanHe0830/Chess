// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAttackAbility.h"

#include "Chess/Actor/ChessPoint.h"
#include "Chess/ChessGamePlayTag.h"
#include "Chess/GameMode/ChessGameMode.h"
#include "Chess/Rule/ChessAttackRule.h"

UChessAttackAbility::UChessAttackAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnly;
	
	FAbilityTriggerData Trigger;
	Trigger.TriggerTag = ChessGameplayTags::Chess_Attack;
	Trigger.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Trigger);
}

void UChessAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AChessPoint* Piece = Cast<AChessPoint>(GetAvatarActorFromActorInfo());
	UChessAttackRule* Rule = Piece ? Piece->GetChessAttackRule() : nullptr;
	UWorld* World = Piece ? Piece->GetWorld() : nullptr;
	AChessGameMode* GameMode = World ? World->GetAuthGameMode<AChessGameMode>() : nullptr;
	if (!Piece || !Rule || !GameMode)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	TArray<AChessPoint*> Targets;
	Rule->CollectTargets(Piece, GameMode, Targets);

	UE_LOG(LogTemp, Warning, TEXT("UChessAttackAbility::ActivateAbility targets=%d"), Targets.Num());
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UChessAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	UE_LOG(LogTemp , Warning , TEXT("UChessAttackAbility::EndAbility"));
}
