// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWD/CategoryContainerWD/GS_CategoryContainerWD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Systems/Inventory/InventoryData.h"
#include "Systems/Inventory/InventoryDataComponent/GS_InventoryDataComponent.h"
#include "UI/InventoryWD/InventorySlotWD/GS_InventorySlotWD.h"


UGS_CategoryContainerWD::UGS_CategoryContainerWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGS_CategoryContainerWD::InitializeCategoryContainerWD(ECategories CategoryType, UGS_InventoryDataComponent* InventoryDataComponent, const FLinearColor& Color)
{
	InventoryComponent = InventoryDataComponent;
	CurrentCategory = CategoryType;
	
	if( IsValid(CategoryColor) )
	{
		CategoryColor->SetColorAndOpacity(Color);
	}

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECategories"), true);
	if ( !IsValid(EnumPtr) || !IsValid(CategoryNameTextBox) ) return;

	CategoryNameTextBox->SetText(FText::FromString(EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(CategoryType)).ToString()));
}

bool UGS_CategoryContainerWD::UpdateCategory()
{
	if( !IsValid(InventoryPanel) || !IsValid(InventoryComponent) ) return false;
	
	InventoryPanel->ClearChildren();

	int32 NewWeight = 0;

	int32 InRow = 0;
	int32 InColumn = -1;

	bool HasItem = false;

	for( const auto& Item : InventoryComponent->GetItems() )
	{
		if( Item.Category == CurrentCategory )
		{
			HasItem = true;
			
			if( InColumn >= MaxColumnsInRow )
			{
				InColumn = 0;
				++InRow;
			}
			else ++InColumn;

			NewWeight += Item.Weight;
			
			CreateSlotWithInfo(Item, InRow, InColumn);
		}
	}

	if( !HasItem ) return false;

	if( IsValid(WeightText) ) WeightText->SetText(FText::FromString(FString::FromInt(NewWeight)));

	return true;
}

bool UGS_CategoryContainerWD::CreateSlotWithInfo(const FItemInfo& NewItemInfo, int32 InRow, int32 InColumn)
{
	if( !IsValid(InventoryPanel) ) return false;
	
	UGS_InventorySlotWD* LInventorySlot = CreateWidget<UGS_InventorySlotWD>(this, InventorySlotClass);
	if( !IsValid(LInventorySlot) ) return false;

	LInventorySlot->InitializeInventorySlotWD(NewItemInfo);

	int32 CurrentWeight = FCString::Atoi(*WeightText->GetText().ToString());
	CurrentWeight += NewItemInfo.Weight;
	WeightText->SetText(FText::FromString(FString::FromInt(CurrentWeight)));
	
	InventoryPanel->AddChildToUniformGrid(LInventorySlot, InRow, InColumn);

	return true;
}
