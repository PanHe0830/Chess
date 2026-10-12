// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "BeginPlayWidget.h"
#include "Chess/GameState/ChessGameState.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"
#include "Components/TextBlock.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CampName->SetText(FText::FromString(TEXT("")));
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWidget::InitializeWidget()
{
	UChessManagerSubsystem* Manager = GetGameInstance()->GetSubsystem<UChessManagerSubsystem>();
	if (Manager)
	{
		UBeginPlayWidget* BeginPlayWidget = Cast<UBeginPlayWidget>(Manager->GetWidgetByName("WBP_BeginPlayWidget"));
		if (BeginPlayWidget && BeginOverlay)
		{
			//BeginPlayWidget->RemoveFromParent();
			if (UOverlaySlot* OverlaySlot = BeginOverlay->AddChildToOverlay(BeginPlayWidget))
			{
				OverlaySlot->SetHorizontalAlignment(HAlign_Center);
				OverlaySlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
	
	if (AChessGameState* ChessGS = GetWorld() ? GetWorld()->GetGameState<AChessGameState>() : nullptr)
	{
		ChessGS->OnTurnChanged.AddDynamic(this, &UMainWidget::HandleTurnChanged);
		HandleTurnChanged(ChessGS->CurrentTurn);
	}
}

void UMainWidget::HandleTurnChanged(EChessTurn NewTurn)
{
	if (!CampName)
	{
		return;
	}
	const FText TurnText = NewTurn == EChessTurn::EXT_Red
		? FText::FromString(TEXT("红方"))
		: FText::FromString(TEXT("蓝方"));
	CampName->SetText(TurnText);
}