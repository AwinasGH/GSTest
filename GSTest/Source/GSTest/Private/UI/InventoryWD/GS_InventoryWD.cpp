// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWD/GS_InventoryWD.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Systems/Inventory/InventoryDataComponent/GS_InventoryDataComponent.h"
#include "UI/InventoryWD/CategoryContainerWD/GS_CategoryContainerWD.h"


UGS_InventoryWD::UGS_InventoryWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UGS_InventoryWD::InitializeInventoryWD(AGS_GameHUD* InGameHUD, UGS_InventoryDataComponent* InventoryDataComponent)
{
	GameHUD = InGameHUD;
	InventoryComponent = InventoryDataComponent;
	
	OnInventoryUpdate();
	
	InitializeVariantComboBox();

	InventoryComponent->OnInventoryChangedBind.AddDynamic(this, &UGS_InventoryWD::OnInventoryUpdate);
	
	if( IsValid(RemoveItemButton) ) RemoveItemButton->OnClicked.AddDynamic(this, &UGS_InventoryWD::OnRemoveButtonClicked);
	if( IsValid(AddItemButton) ) AddItemButton->OnClicked.AddDynamic(this, &UGS_InventoryWD::OnAddButtonClicked);
}

void UGS_InventoryWD::OnInventoryUpdate()
{
	UpdateCategories();

	UpdateWeightInfo();
}


void UGS_InventoryWD::UpdateWeightInfo()
{
	int32 CurrentWeight = FMath::Clamp(InventoryComponent->GetCurrentInventoryWeight(), 0, InventoryComponent->MaxWeight);

	if( IsValid(WeightText) )
	{
		WeightText->SetText(FText::FromString(FString::FromInt(CurrentWeight) + "/" + FString::FromInt(InventoryComponent->MaxWeight)));
	}

	if( !IsValid(WeightProgressBox) ) return;

	WeightProgressBox->ClearChildren();
	
	TMap<ECategories, int32> CategoriesWeights;

	for( const auto& CategoryColor : CategoriesColors )
	{
		CategoriesWeights.Add(CategoryColor.Key, 0);
	}
	
	for( const auto& Item : InventoryComponent->GetItems() )
	{
		if( CategoriesWeights.Contains(Item.Category) )
		{
			int32& ItemWeight = CategoriesWeights.FindChecked(Item.Category);
			ItemWeight += Item.Weight;
		}
	}
	
	CategoriesWeights.ValueSort([](const int32& Left, const int32& Right)
	{
		return Left > Right;
	});
	
	for (const auto& CategoryWeight : CategoriesWeights)
	{
		CreateProgressImage(CategoryWeight.Value, CategoriesColors.FindRef(CategoryWeight.Key));
	}

	CreateProgressImage(InventoryComponent->MaxWeight - CurrentWeight, WeightProgressBackgroundColor);
}

void UGS_InventoryWD::UpdateCategories()
{
	if( !IsValid(CategoryContainerClass) ) return;
	
	if( !CategoryWDs.IsEmpty() )
	{
		for( const auto& CategoryWD : CategoryWDs )
		{
			CategoryWD.Value->RemoveFromParent();
		}

		CategoryWDs.Empty();
	}
	
	for( const auto& Item : InventoryComponent->GetItems() )
	{
		UGS_CategoryContainerWD* CategoryWD = nullptr;
		
		if( !IsValid(CategoryWDs.FindRef(Item.Category)) )
		{
			CategoryWD = CreateCategory(Item.Category, CategoriesColors.FindRef(Item.Category));
		}
		
		if( IsValid(CategoryWD) )
		{
			bool SuccessfullyUpdated = CategoryWD->UpdateCategory();

			if( !SuccessfullyUpdated )
			{
				CategoryWD->RemoveFromParent();
			}
		}
	}

}

void UGS_InventoryWD::CreateProgressImage(int32 CategoryWeight, FLinearColor Color)
{
	UImage* CategoryWeightImage = WidgetTree->ConstructWidget<UImage>();
	if ( IsValid(CategoryWeightImage) )
	{
		CategoryWeightImage->SetColorAndOpacity(Color);
			
		WeightProgressBox->AddChildToHorizontalBox(CategoryWeightImage);

		UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(CategoryWeightImage->Slot.Get());
		if( IsValid(HorizontalBoxSlot) )
		{
			FSlateChildSize NewSize(ESlateSizeRule::Fill);
			NewSize.Value = CategoryWeight;
				
			HorizontalBoxSlot->SetSize(NewSize);
		}
	}
}

void UGS_InventoryWD::OnAddButtonClicked()
{
	if( !IsValid(ItemVariantComboBox) || !IsValid(InventoryComponent) ) return;

	TArray<FItemInfo*> VariantItems;
	InventoryComponent->ItemsToAddData->GetAllRows<FItemInfo>("GetItems", VariantItems);

	for( const FItemInfo* ItemRow : VariantItems )
	{
		if( ItemVariantComboBox->GetSelectedOption() == ItemRow->ItemName.ToString() )
		{
			InventoryComponent->AddItemToInventory(*ItemRow);

			break;
		}
	}
}

void UGS_InventoryWD::OnRemoveButtonClicked()
{
	if( !IsValid(InventoryComponent) ) return;
	
	for( const FItemInfo& ItemRow : InventoryComponent->GetItems() )
	{
		if( ItemVariantComboBox->GetSelectedOption() == ItemRow.ItemName.ToString() )
		{
			InventoryComponent->RemoveItemFromInventory(ItemRow);

			break;
		}
	}
}

void UGS_InventoryWD::InitializeVariantComboBox()
{
	if( !IsValid(InventoryComponent->ItemsToAddData) || !IsValid(ItemVariantComboBox) ) return;
	
	TArray<FItemInfo*> VariantItems;
	InventoryComponent->ItemsToAddData->GetAllRows<FItemInfo>("GetItems", VariantItems);

	for( const FItemInfo* ItemRow : VariantItems )
	{
		ItemVariantComboBox->AddOption(ItemRow->ItemName.ToString());
	}
}


UGS_CategoryContainerWD* UGS_InventoryWD::CreateCategory(ECategories NewCategory, const FLinearColor& Color)
{
	if( !IsValid(CategoryContainerClass) ) return nullptr;
	
	UGS_CategoryContainerWD* LInventoryCategory = CreateWidget<UGS_CategoryContainerWD>(this, CategoryContainerClass);

	if( IsValid(CategoriesWDsScrollBox) ) CategoriesWDsScrollBox->AddChild(LInventoryCategory);

	LInventoryCategory->InitializeCategoryContainerWD(NewCategory, InventoryComponent, Color);

	CategoryWDs.Add(NewCategory, LInventoryCategory);

	return LInventoryCategory;
}



