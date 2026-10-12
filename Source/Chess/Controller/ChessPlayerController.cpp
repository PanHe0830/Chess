// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Chess/ChessGamePlayTag.h"
#include "Chess/Actor/ChessBoard.h"
#include "Chess/Actor/ChessPoint.h"
#include "Chess/GameMode/ChessGameMode.h"
#include "Chess/PlayerState/ChessPlayerState.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"
#include "Chess/UI/MainWidget.h"
#include "Components/TextBlock.h"

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
	//UChessManagerSubsystem* ChessManager = GetGameInstance()
	//	? GetGameInstance()->GetSubsystem<UChessManagerSubsystem>()
	//	: nullptr;
	//if (!ChessManager)
	//{
	//	return;
	//}
	//
	//FHitResult Hit;
	//if (!GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	//{
	//	return;
	//}
	//
	//AChessPoint* HitPiece = Cast<AChessPoint>(Hit.GetActor());
	//AChessPoint* SelectedPiece = Cast<AChessPoint>(ChessManager->GetCurrentSelectedActor());
	//
	//if (HitPiece)
	//{
	//	const bool bCanCapture = SelectedPiece
	//		&& SelectedPiece != HitPiece
	//		&& SelectedPiece->GetChessCamp() != HitPiece->GetChessCamp()
	//		&& SelectedPiece->GetChessCamp() != EChessCamp::ECT_MAX
	//		&& HitPiece->GetChessCamp() != EChessCamp::ECT_MAX;
	//
	//	if (bCanCapture)
	//	{
	//		const FVector TargetLocation = HitPiece->GetLogicalLocation();
	//		ChessManager->SetCurrentSelectedActor(nullptr);
	//		ServerRequestChessMove(SelectedPiece, TargetLocation);
	//		return;
	//	}
	//
	//	ChessManager->SetCurrentSelectedActor(HitPiece);
	//	return;
	//}
	//
	//if (!SelectedPiece)
	//{
	//	return;
	//}
	//
	//const float LogicalZ = SelectedPiece->GetLogicalLocation().Z;
	//ChessManager->SetCurrentSelectedActor(nullptr);
	//
	//FVector TargetLocation(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, LogicalZ);
	//if (const AChessBoard* Board = Cast<AChessBoard>(Hit.GetActor()))
	//{
	//	const FVector BoardLocation = Board->GetActorLocation();
	//	TargetLocation.X = BoardLocation.X;
	//	TargetLocation.Y = BoardLocation.Y;
	//}
	//
	//ServerRequestChessMove(SelectedPiece, TargetLocation);
}

void AChessPlayerController::MouseRightButtonClicked(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("AChessPlayerController::MouseRightButtonClicked"));
	//if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
	//{
	//	ChessManager->SetCurrentSelectedActor(nullptr);
	//}
}

void AChessPlayerController::ServerNotifyReady_Implementation()
{
	if (AChessPlayerState* ChessPlayerState = GetPlayerState<AChessPlayerState>())
	{
		ChessPlayerState->SetReady(true);
	}

	if (AChessGameMode* ChessGameMode = GetWorld() ? GetWorld()->GetAuthGameMode<AChessGameMode>() : nullptr)
	{
		ChessGameMode->NotifyPlayerReady();
	}
}

void AChessPlayerController::ClientCloseReadyWidget_Implementation()
{
	UGameInstance* GameInstance = GetGameInstance();
	UChessManagerSubsystem* Manager = GameInstance ? GameInstance->GetSubsystem<UChessManagerSubsystem>() : nullptr;
	if (!Manager)
	{
		return;
	}

	if (UUserWidget* ReadyWidget = Manager->GetWidgetByName(TEXT("WBP_BeginPlayWidget")))
	{
		ReadyWidget->RemoveFromParent();
	}
	if (UMainWidget* ReadyWidget = Cast<UMainWidget>(Manager->GetWidgetByName(TEXT("WBP_MainWidget"))))
	{
		ReadyWidget->CampName->SetText(FText::FromString(TEXT("红方")));
	}
}

void AChessPlayerController::ServerRequestChessMove_Implementation(class AChessPoint* Piece, FVector_NetQuantize TargetLocation)
{
	FGameplayEventData EventData;
	EventData.EventTag = ChessGameplayTags::Chess_Move;
	EventData.Instigator = this;
	EventData.Target = Piece;

	FGameplayAbilityTargetData_LocationInfo* LocData = new FGameplayAbilityTargetData_LocationInfo();
	LocData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	LocData->TargetLocation.LiteralTransform = FTransform(TargetLocation);
	EventData.TargetData = FGameplayAbilityTargetDataHandle(LocData);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Piece,
		ChessGameplayTags::Chess_Move,
		EventData);

	UE_LOG(LogTemp, Warning, TEXT("Request move %s to %s (from %s)"),
		*Piece->GetName(),
		*TargetLocation.ToCompactString(),
		*TargetLocation.ToCompactString());
}
