// Fill out your copyright notice in the Description page of Project Settings.


#include "BeginPlayWidget.h"

#include "Components/Button.h"
#include "Chess/Controller/ChessPlayerController.h"

void UBeginPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ReadyButton)
	{
		ReadyButton->OnClicked.AddDynamic(this, &UBeginPlayWidget::OnReadyButtonClicked);
	}
}

void UBeginPlayWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (ReadyButton)
	{
		ReadyButton->OnClicked.RemoveAll(this);
	}
}

void UBeginPlayWidget::OnReadyButtonClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC && GetWorld())
	{
		PC = GetWorld()->GetFirstPlayerController();
	}

	if (AChessPlayerController* ChessPC = Cast<AChessPlayerController>(PC))
	{
		ChessPC->ServerNotifyReady();
	}
}
