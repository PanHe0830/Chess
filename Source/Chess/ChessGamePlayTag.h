// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace ChessGameplayTags
{
	CHESS_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString);
	
	CHESS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Chess_Move);
}