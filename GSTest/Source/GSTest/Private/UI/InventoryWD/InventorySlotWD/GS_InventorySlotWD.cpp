// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWD/InventorySlotWD/GS_InventorySlotWD.h"

#include "Components/Image.h"
#include "Systems/Inventory/InventoryData.h"


UGS_InventorySlotWD::UGS_InventorySlotWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UGS_InventorySlotWD::InitializeInventorySlotWD(const FItemInfo& ItemInfo)
{
	FSlateBrush SlateBrush;
	SlateBrush.SetResourceObject(ItemInfo.ItemImage);
	
	if( IsValid(SlotImage) )
	{
		SlotImage->SetBrush(SlateBrush);
	}
}
