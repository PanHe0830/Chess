// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Abilities/Tasks/AbilityTask_MoveToLocation.h"
#include "Chess/ChessGamePlayTag.h"
#include "GameFramework/Actor.h"

UChessMoveAbility::UChessMoveAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnly;
	
	bServerRespectsRemoteAbilityCancellation = true;
	bRetriggerInstancedAbility = false;
	bReplicateInputDirectly = true;
	
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
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* Avatar = GetAvatarActorFromActorInfo();
	if (!Avatar || !TriggerEventData || !TriggerEventData->TargetData.IsValid(0))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FGameplayAbilityTargetData* TargetData = TriggerEventData->TargetData.Get(0);
	const FVector TargetLocation = TargetData->GetEndPoint();

	UAbilityTask_MoveToLocation* MoveTask = UAbilityTask_MoveToLocation::MoveToLocation(this,NAME_None,TargetLocation,0.25,nullptr,nullptr);
	if (!MoveTask)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	MoveTask->OnTargetLocationReached.AddDynamic(this, &UChessMoveAbility::OnMoveReached);
	MoveTask->ReadyForActivation();
}

void UChessMoveAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* Avatar = ActorInfo ? ActorInfo->AvatarActor.Get() : nullptr;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// 移动被取消/失败时不接攻击
	if (bWasCancelled || !Avatar)
	{
		return;
	}
	
	FGameplayEventData AttackEvent;
	AttackEvent.EventTag = ChessGameplayTags::Chess_Attack;
	AttackEvent.Instigator = Avatar;
	AttackEvent.Target = Avatar;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Avatar,
		ChessGameplayTags::Chess_Attack,
		AttackEvent);
}

void UChessMoveAbility::OnMoveReached()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
