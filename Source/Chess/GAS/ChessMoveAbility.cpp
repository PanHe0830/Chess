// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveAbility.h"

#include "Chess/ChessGamePlayTag.h"

UChessMoveAbility::UChessMoveAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
	
	bServerRespectsRemoteAbilityCancellation = true;
	bRetriggerInstancedAbility = false;
	bReplicateInputDirectly = false;
	
	FAbilityTriggerData Trigger;
	Trigger.TriggerTag = ChessGameplayTags::Chess_Move;
	Trigger.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Trigger);
}

void UChessMoveAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
	)
{
	UE_LOG(LogTemp , Warning , TEXT("UChessMoveAbility::ActivateAbility"));
}

void UChessMoveAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
