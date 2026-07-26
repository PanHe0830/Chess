// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetShowMouseCursor(true);
}

void AChessPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// 2. 获取增强输入子系统，用于添加映射上下文
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// 确保你的 InputMappingContext 资源已正确加载
		Subsystem->AddMappingContext(YourInputMappingContext, 0);
	}

	// 3. 将 InputComponent 转换为增强输入组件，进行绑定
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(YourInputAction, ETriggerEvent::Triggered, this, &AMyPlayerController::YourFunction);
	}
}
