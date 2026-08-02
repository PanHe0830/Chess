// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Chess/ChessGamePlayTag.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetShowMouseCursor(true);
}

void AChessPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UE_LOG(LogTemp, Warning, TEXT("AChessPlayerController::SetupInputComponent"));
	
	// 2. 获取增强输入子系统，用于添加映射上下文
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// 确保你的 InputMappingContext 资源已正确加载
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// 3. 将 InputComponent 转换为增强输入组件，进行绑定
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MouseLeftDown, ETriggerEvent::Triggered, this, &AChessPlayerController::MouseLeftButtonClicked);
		EnhancedInput->BindAction(MouseRightDown, ETriggerEvent::Triggered, this, &AChessPlayerController::MouseRightButtonClicked);
	}
}

void AChessPlayerController::MouseLeftButtonClicked(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AChessPlayerController::MouseLeftButtonClicked"));
	FHitResult Hit;
	const bool bHit = GetHitResultUnderCursor(
		ECC_Visibility,
		false,
		Hit
	);
	
	if (!bHit)
	{
		return;
	}
	
	if (AChessPoint* Piece = Cast<AChessPoint>(Hit.GetActor()))
	{
		if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
		{
			ChessManager->SetCurrentSelectedActor(Piece);
		}
		UE_LOG(LogTemp, Warning, TEXT("Selected: %s"), *Piece->GetName());
	}
	else
	{
		UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>();
		AChessPoint* ChessPoint = ChessManager ? Cast<AChessPoint>(ChessManager->GetCurrentSelectedActor()): nullptr;
		if (!ChessPoint)
		{
			return;
		}

		// 先取消选中，把抬起的 Z 降回去，再用逻辑高度作为落点 Z
		const FVector CurrentLocation = ChessPoint->GetActorLocation();
		ChessManager->SetCurrentSelectedActor(nullptr);
		const FVector LogicalLocation = ChessPoint->GetActorLocation();

		const FVector TargetLocation(
			Hit.ImpactPoint.X,
			Hit.ImpactPoint.Y,
			LogicalLocation.Z);

		FGameplayEventData EventData;
		EventData.EventTag = ChessGameplayTags::Chess_Move;
		EventData.Instigator = this;
		EventData.Target = ChessPoint;

		FGameplayAbilityTargetData_LocationInfo* LocData = new FGameplayAbilityTargetData_LocationInfo();
		LocData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
		LocData->TargetLocation.LiteralTransform = FTransform(TargetLocation);
		EventData.TargetData = FGameplayAbilityTargetDataHandle(LocData);

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			ChessPoint,
			ChessGameplayTags::Chess_Move,
			EventData);

		UE_LOG(LogTemp, Warning, TEXT("Request move %s to %s (from %s)"),
			*ChessPoint->GetName(),
			*TargetLocation.ToCompactString(),
			*CurrentLocation.ToCompactString());
	}
}

void AChessPlayerController::MouseRightButtonClicked(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AChessPlayerController::MouseRightButtonClicked"));
	if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
	{
		ChessManager->SetCurrentSelectedActor(nullptr);
	}
}
