// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
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
		//if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
		//{
		//	ChessManager->SetCurrentSelectedActor(nullptr);
		//}
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
		if (UChessManagerSubsystem* ChessManager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>())
		{
			ChessManager->SetCurrentSelectedActor(nullptr);
		}
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
