// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoveAbility.h"

#include "Abilities/GameplayAbilityTargetTypes.h"
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

	Avatar->SetActorLocation(TargetLocation);

	UE_LOG(LogTemp, Warning, TEXT("UChessMoveAbility::ActivateAbility move to %s"),
		*TargetLocation.ToCompactString());

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UChessMoveAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
