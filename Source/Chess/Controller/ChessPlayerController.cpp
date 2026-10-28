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
#include "Chess/Rule/ChessMoveBase.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"
#include "Chess/UI/MainWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	
	//if (IsLocalController())
	//{
	//	bShowMouseCursor = true;
	//	bEnableClickEvents = true;
	//	bEnableMouseOverEvents = true;
	//
	//	FInputModeGameAndUI InputMode;
	//	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//	InputMode.SetHideCursorDuringCapture(false);
	//	SetInputMode(InputMode);
	//
	//	// 点选棋子时不要把鼠标位移当成视角输入，避免画面微抖
	//	SetIgnoreLookInput(true);
	//}
}

void AChessPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (P)
	{
		P->SetActorHiddenInGame(true);
	}

	//if (IsLocalController())
	//{
	//	SetIgnoreLookInput(true);
	//}

	ApplyStartViewRotation();
}

void AChessPlayerController::SetStartViewRotation(const FRotator& NewRotation)
{
	bHasStartViewRotation = true;
	StartViewRotation = NewRotation;
	ApplyStartViewRotation();
	ClientSetRotation(NewRotation, true);
}

void AChessPlayerController::ApplyStartViewRotation()
{
	if (!bHasStartViewRotation)
	{
		return;
	}

	SetControlRotation(StartViewRotation);
}

void AChessPlayerController::OnRep_StartViewRotation()
{
	bHasStartViewRotation = true;
	ApplyStartViewRotation();
}

void AChessPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChessPlayerController, StartViewRotation);
	DOREPLIFETIME(AChessPlayerController, bHasStartViewRotation);
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
	UChessManagerSubsystem* ChessManager = GetGameInstance()
		? GetGameInstance()->GetSubsystem<UChessManagerSubsystem>()
		: nullptr;
	if (!ChessManager)
	{
		return;
	}
	
	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		return;
	}
	
	AChessPoint* HitPiece = Cast<AChessPoint>(Hit.GetActor());
	AChessBoard* HitBoard = Cast<AChessBoard>(Hit.GetActor());
	AChessPoint* SelectedPiece = Cast<AChessPoint>(ChessManager->GetCurrentSelectedActor());
	
	if (HitPiece)
	{
		const bool bCanCapture = SelectedPiece
			&& SelectedPiece != HitPiece
			&& SelectedPiece->GetChessCamp() != HitPiece->GetChessCamp()
			&& SelectedPiece->GetChessCamp() != EChessCamp::ECT_MAX
			&& HitPiece->GetChessCamp() != EChessCamp::ECT_MAX;
	
		if (bCanCapture)
		{
			const FVector2D Target = HitPiece->GetBoardPoint();
			ChessManager->SetCurrentSelectedActor(nullptr);
			ServerRequestChessMove(SelectedPiece,HitPiece->GetActorLocation(), Target);
			return;
		}
	
		ChessManager->SetCurrentSelectedActor(HitPiece);
		return;
	}
	
	if (!SelectedPiece || !HitBoard)
	{
		return;
	}
	
	const float LogicalZ = SelectedPiece->GetLogicalLocation().Z;
	ChessManager->SetCurrentSelectedActor(nullptr);
	
	FVector TargetLocation(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, LogicalZ);
	if (const AChessBoard* Board = Cast<AChessBoard>(Hit.GetActor()))
	{
		const FVector BoardLocation = Board->GetActorLocation();
		TargetLocation.X = BoardLocation.X;
		TargetLocation.Y = BoardLocation.Y;
	}
	
	ServerRequestChessMove(SelectedPiece, TargetLocation,HitBoard->GetBoardPoint());
}

void AChessPlayerController::MouseRightButtonClicked(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AChessPlayerController::MouseRightButtonClicked"));
	if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
	{
		ChessManager->SetCurrentSelectedActor(nullptr);
	}
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

void AChessPlayerController::ServerRequestChessMove_Implementation(class AChessPoint* Piece, FVector_NetQuantize TargetLocation,FVector2D Targert)
{
	FGameplayEventData EventData;
	EventData.EventTag = ChessGameplayTags::Chess_Move;
	EventData.Instigator = this;
	EventData.Target = Piece;

	FGameplayAbilityTargetData_LocationInfo* LocData = new FGameplayAbilityTargetData_LocationInfo();
	LocData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	LocData->TargetLocation.LiteralTransform = FTransform(TargetLocation);
	EventData.TargetData = FGameplayAbilityTargetDataHandle(LocData);
	
	UChessMoveBase* MoveRule = Piece->GetChessMoveRule();
	AChessGameMode* GM = Cast<AChessGameMode>(UGameplayStatics::GetGameMode(this));
	if (!MoveRule || !GM) return;
	if (!MoveRule->IsMoveLegal(Piece->GetChessCamp(),Piece->GetBoardPoint(), Targert,GM->GetOccupiedCells()))
	{
		return;	
	}

	GM->UpdateChessPointPosition(Piece,Targert);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Piece,
		ChessGameplayTags::Chess_Move,
		EventData);
	
	FGameplayEventData AttackEvent;
	AttackEvent.EventTag = ChessGameplayTags::Chess_Attack;
	AttackEvent.Instigator = Piece;
	AttackEvent.Target = Piece;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Piece, 
		ChessGameplayTags::Chess_Attack, 
		AttackEvent);

	UE_LOG(LogTemp, Warning, TEXT("Request move %s to %s (from %s)"),
		*Piece->GetName(),
		*TargetLocation.ToCompactString(),
		*TargetLocation.ToCompactString());
}
