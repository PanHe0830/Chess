// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "BeginPlayWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Chess/SubSystem/ChessManagerSubsystem.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
}
