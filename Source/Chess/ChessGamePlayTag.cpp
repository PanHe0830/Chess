// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessGamePlayTag.h"
#include "Modules/ModuleManager.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace ChessGameplayTags
{
	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Chess_Move, "Ability.Chess.Move", "Chess Move.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Chess_Attack, "Ability.Chess.Attack", "Chess Attack.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Chess_Defense, "Ability.Chess.Defense", "Chess Defense.");
	
}