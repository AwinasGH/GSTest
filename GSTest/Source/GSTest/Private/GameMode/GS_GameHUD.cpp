// Fill out your copyright notice in the Description page of Project Settings.


#include "GSTest/Public/GameMode/GS_GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "GSTest/Public/Player/GS_PlayerController.h"
#include "UI/InventoryWD/GS_InventoryWD.h"

AGS_GameHUD::AGS_GameHUD()
{
	
}

void AGS_GameHUD::SetFocusToWidget(EWidgetFocusType WidgetFocusType, UUserWidget* Widget)
{
	if( !IsValid(Widget) ) return;


	switch( WidgetFocusType )
	{
	case EWidgetFocusType::GameOnly:
		{
			FInputModeGameOnly LNewGameOnlyInput;
			MyController->SetInputMode(LNewGameOnlyInput);
			break;
		}

	case EWidgetFocusType::UIOnly:
		{
			FInputModeUIOnly LNewUIOnlyInput;
			LNewUIOnlyInput.SetWidgetToFocus(Widget->TakeWidget());
			MyController->SetInputMode(LNewUIOnlyInput);
			break;
		}

	case EWidgetFocusType::GameAndUI:
		{
			FInputModeGameAndUI LNewGameAndUIInput;
			LNewGameAndUIInput.SetWidgetToFocus(Widget->TakeWidget());
			MyController->SetInputMode(LNewGameAndUIInput);
			break;
		}
	}

	if( Widget->bIsFocusable ) Widget->SetKeyboardFocus();
}

void AGS_GameHUD::AddWidgetToFocusStack(EWidgetFocusType WidgetFocusType, UUserWidget* Widget)
{
	if( !IsValid(Widget) ) return;


	if( WidgetFocusStack.Num() == 0 || WidgetFocusStack[WidgetFocusStack.Num() - 1].Widget != Widget )
	{
		WidgetFocusStack.Add(FWidgetFocusInfo(WidgetFocusType, Widget));
	}
}

void AGS_GameHUD::RemoveWidgetFromFocusStack(UUserWidget* Widget)
{
	WidgetFocusStack.RemoveAll([Widget](const FWidgetFocusInfo& LInfo) { return LInfo.Widget == Widget || !IsValid(LInfo.Widget); });
}

void AGS_GameHUD::FocusLastWidgetInStack()
{
	if( WidgetFocusStack.Num() > 0 )
	{
		const FWidgetFocusInfo& LWidgetFocusInfo = WidgetFocusStack[WidgetFocusStack.Num() - 1];
		SetFocusToWidget(LWidgetFocusInfo.FocusType, LWidgetFocusInfo.Widget);
	}
}

void AGS_GameHUD::ClearWidgetFocusStack()
{
	WidgetFocusStack.Empty();
}

void AGS_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	MyController = Cast<AGS_PlayerController>(GetOwningPlayerController());
}

void AGS_GameHUD::CreateInventoryWD()
{
	if( !InventoryWDClass.IsNull() && !InventoryWD && IsValid(MyController) )
	{
		InventoryWD = CreateWidget<UGS_InventoryWD>(GetWorld(), InventoryWDClass.LoadSynchronous());
		if( InventoryWD ) InventoryWD->InitializeInventoryWD(this, MyController->InventoryData);
		if( InventoryWD ) InventoryWD->AddToViewport();
	}

	SetFocusToInventoryWD();
}

void AGS_GameHUD::SetFocusToInventoryWD()
{
	if( InventoryWD )
	{
		MyController->SetShowMouseCursor(true);

		AddWidgetToFocusStack(EWidgetFocusType::UIOnly, InventoryWD);
		SetFocusToWidget(EWidgetFocusType::UIOnly, InventoryWD);
	}
}

void AGS_GameHUD::RemoveInventoryWD()
{
	if( InventoryWD )
	{
		RemoveWidgetFromFocusStack(InventoryWD);
		FocusLastWidgetInStack();

		InventoryWD->RemoveFromParent();
		InventoryWD = nullptr;

		MyController->SetShowMouseCursor(false);
		MyController->SetInputMode(FInputModeGameOnly());
	}
}
